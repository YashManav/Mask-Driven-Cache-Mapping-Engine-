#include <bits/stdc++.h>
using namespace std;

ofstream fout("trace.csv");

long long parseSize(string s) {
    stringstream ss(s);
    long long value;
    string unit;
    ss >> value >> unit;

    if (unit == "KB") return value*(1LL << 10);
    if (unit == "MB") return value*(1LL << 20);
    if (unit == "GB") return value*(1LL << 30);
    if (unit == "TB") return value*(1LL << 40);

    return value;
}

int log2ll(long long x) {
    return log2(x);
}

void traceGenerator(vector<string> &traces, int rowIndex) {

    int linear = stoi(traces[0]);
    long long memory = parseSize(traces[1]);
    long long working_set = parseSize(traces[2]);
    int sets = stoi(traces[3]);
    long long cache_size = parseSize(traces[4]);
    int mask_bits = stoi(traces[5]);
    int ways = stoi(traces[6]);

    int address_bits = log2ll(memory);
    int working_bits = log2ll(working_set);

    long long block_size = cache_size /(sets*ways);         
    int offset_bits = log2ll(block_size);
    int fixed_bits = address_bits-working_bits;

    long long fixed_part = (1LL<<fixed_bits)-1;
    int total = 1<<15;
    for(int i = 0; i < total; i++) 
    {
        long long index_val;
        if(linear == 0){
            index_val = i;
        } 
        else
        {
            index_val = rand() % (1LL << (working_bits - offset_bits));
        }
        long long address = (fixed_part << working_bits) | (index_val << offset_bits);

        fout << rowIndex << "," << i << "," << address << "\n";
    }
}

int main() 
{
    srand(time(0));
    ifstream fin("datafortrace.csv");
    string line;
    int index = 0;
    while (getline(fin, line)) 
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string s;
        vector<string> columns;
        while(getline(ss, s, ',')) 
        {
            columns.push_back(s);
        }
        if(index == 0 && !isdigit(columns[0][0])) 
        {
            fout << "Row,Index,Address\n";
            index++;
            continue;
        }
        traceGenerator(columns, index);
        index++;
    }

    fin.close();
    fout.close();

    return 0;
}