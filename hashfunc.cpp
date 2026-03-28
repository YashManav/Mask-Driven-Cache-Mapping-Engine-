#include <bits/stdc++.h>
using namespace std;


long long parseSize(string s) {
    stringstream ss(s);
    long long value;
    string unit;
    ss>>value>>unit;

    if(unit == "KB") 
    return value * (1LL << 10);
    if(unit == "MB") 
    return value * (1LL << 20);
    if(unit == "GB") 
    return value * (1LL << 30);
    if(unit == "TB") 
    return value * (1LL << 40);

    return value;
}

int log2ll(long long x) 
{
    return log2(x);
}

int parity(long long x) 
{
    int p = 0;
    while(x) 
    {
        p ^= (x & 1);
        x >>= 1;
    }
    return p;
}

int getSet(long long address, vector<long long> &masks) {
    int set = 0;
    for (int i = 0; i < masks.size(); i++) {
        int bit = parity(address & masks[i]);
        set |= (bit << i);
    }
    return set;
}

int main() {

    srand(time(0));
    unordered_map<int, vector<long long>> masks_map;
    ifstream maskFile("mask.csv");
    string line;

    getline(maskFile, line);
    while(getline(maskFile, line)) 
    {
        stringstream ss(line);
        string s;
        vector<string> cols;
        while(getline(ss, s, ',')) 
        cols.push_back(s);

        int row = stoi(cols[0]);
        long long mask = stoll(cols[2]);

        masks_map[row].push_back(mask);
    }
    maskFile.close();

    unordered_map<int, vector<long long>> trace_map;
    ifstream traceFile("trace.csv");
    getline(traceFile, line);
    while(getline(traceFile, line)) 
    {
        stringstream ss(line);
        string s;
        vector<string> cols;

        while (getline(ss, s, ',')) cols.push_back(s);

        int row = stoi(cols[0]);
        long long address = stoll(cols[2]);

        trace_map[row].push_back(address);
    }
    traceFile.close();
    ifstream dataFile("datafortrace.csv");
    ofstream fout("stats.csv");

    fout<< "Row,TotalAccess,Hits,Misses,HitRate,MissRate,Utilization(%),Replacements\n";

    int rowIndex = 0;

    while(getline(dataFile, line)) 
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string s;
        vector<string> cols;
        while (getline(ss, s, ',')) cols.push_back(s);

        if(rowIndex == 0 && !isdigit(cols[0][0])) 
        {
            rowIndex++;
            continue;
        }

        long long memory = parseSize(cols[1]);
        int sets = stoi(cols[3]);
        long long cache_size = parseSize(cols[4]);
        int ways = stoi(cols[6]);

        int address_bits = log2ll(memory);
        long long block_size = cache_size / (sets * ways);
        int offset_bits = log2ll(block_size);

        vector<vector<long long>> cache(sets, vector<long long>(ways, -1));
        vector<int> set_access_count(sets, 0);

        int hits = 0, misses = 0, replacements = 0;
        int used_lines = 0;
        vector<long long> &addresses = trace_map[rowIndex];
        vector<long long> &masks = masks_map[rowIndex];

        for(long long address : addresses) 
        {
            long long block = address >> offset_bits;
            int set = getSet(address, masks);
            set_access_count[set]++;
            bool found = false;
            for(int w = 0; w < ways; w++) 
            {
                if(cache[set][w] == block) 
                {
                    found = true;
                    hits++;
                    break;
                }
            }
            if(!found) 
            {
                misses++;
                bool inserted = false;
                for(int w = 0; w < ways; w++) 
                {
                    if(cache[set][w] == -1) 
                    {
                        cache[set][w] = block;
                        inserted = true;
                        used_lines++;
                        break;
                    }
                }
                if(!inserted) 
                {
                    int victim = rand() % ways;
                    cache[set][victim] = block;
                    replacements++;
                }
            }
        }

        int total = addresses.size();

        double hit_rate = (double)hits / total;
        double miss_rate = (double)misses / total;

        double utilization = (double)used_lines / (sets * ways) * 100.0;
        fout << rowIndex << ","
             << total << ","
             << hits << ","
             << misses << ","
             << hit_rate << ","
             << miss_rate << ","
             << utilization << ","
             << replacements << "\n";
        rowIndex++;
    }
    dataFile.close();
    fout.close();
    return 0;
}