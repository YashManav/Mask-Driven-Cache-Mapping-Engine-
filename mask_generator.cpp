#include <bits/stdc++.h>
using namespace std;

long long parseSize(string s) {
    stringstream ss(s);
    long long value;
    string unit;
    ss >> value >> unit;

    if (unit == "KB") return value * (1LL << 10);
    if (unit == "MB") return value * (1LL << 20);
    if (unit == "GB") return value * (1LL << 30);
    if (unit == "TB") return value * (1LL << 40);

    return value;
}

int log2ll(long long x) {
    return log2(x);
}

int main() {

    srand(time(0));
    ifstream dataFile("datafortrace.csv");
    ofstream fout("mask.csv");
    string line;
    int rowIndex = 0;
    fout<< "Row,MaskIndex,Mask\n";
    while(getline(dataFile, line)) 
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string s;
        vector<string> cols;
        while(getline(ss, s, ',')) 
        {
            cols.push_back(s);
        }
        if(rowIndex == 0 && !isdigit(cols[0][0])) 
        {
            rowIndex++;
            continue;
        }
        long long memory = parseSize(cols[1]);
        int num_masks = stoi(cols[5]);
        int address_bits = log2ll(memory);
        for(int i = 0; i < num_masks; i++) 
        {
            long long mask = 0;
            for(int b = 0; b < address_bits; b++) 
            {
                if(rand() % 2) 
                {
                    mask |= (1LL << b);
                }
            }
            fout<<rowIndex<< "," <<i<< "," << mask << "\n";
        }
        rowIndex++;
    }
    dataFile.close();
    fout.close();
    return 0;
}