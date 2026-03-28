# 🚀 Mask-Driven Cache Mapping Engine

> A **C++ cache simulator** that uses **mask-based hashing (bitwise AND + parity)** to map memory addresses to cache sets and analyze performance.

---

## 📖 Overview

Traditional cache indexing uses simple techniques like modulo or lower address bits, which often cause **conflict misses**.

This project introduces a **mask-driven hashing approach**, where:
- Multiple **bitmasks** are applied to an address  
- Each result is reduced using **parity (XOR)**  
- The resulting bits are combined to generate the **cache set index**

This leads to **better distribution of addresses across cache sets**.

---

## ✨ Key Features

- ⚡ **Custom Hash Function** using bitmask + parity  
- 🔁 Supports **Linear & Random Trace Generation**  
- 🧠 **Set-Associative Cache Simulation**  
- 🎯 **Random Replacement Policy**  
- 📊 Tracks **Hit/Miss Rate, Utilization, Replacements**  
- 📂 Fully **CSV-driven pipeline**

---

## 🧠 Hashing Mechanism


For each mask:
bit_i = parity(address & mask[i])

Set Index = combine(bit_0, bit_1, ..., bit_k)


---

## 📁 Project Structure


.
├── datafortrace.csv # Input configuration
├── trace.csv # Generated addresses
├── mask.csv # Generated masks
├── stats.csv # Output statistics
├── traceGenerator.cpp
├── maskGenerator.cpp
├── cacheSimulator.cpp
└── README.md


---

## ⚙️ Input Format

### datafortrace.csv


Linear/Random, Memory, Working Set, Cache Set, Cache Size, Mask Required, Ways
0, 128 GB, 4 GB, 256, 32 KB, 8, 4


| Column | Meaning |
|------|--------|
| Linear/Random | 0 = sequential, 1 = random |
| Memory | Total memory size |
| Working Set | Active memory region |
| Cache Set | Number of sets |
| Cache Size | Total cache size |
| Mask Required | Number of masks |
| Ways | Associativity |

---

## 🔄 Workflow


datafortrace.csv
↓
traceGenerator → trace.csv
maskGenerator → mask.csv
↓
cacheSimulator
↓
stats.csv


---

## 🛠️ How to Run

### 1️⃣ Compile

```bash
g++ traceGenerator.cpp -o traceGen
g++ maskGenerator.cpp -o maskGen
g++ cacheSimulator.cpp -o simulator
2️⃣ Execute
./traceGen
./maskGen
./simulator
🧩 Core Implementation
🔹 Hash Function
int parity(long long x) {
    int p = 0;
    while (x) {
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
🔹 Cache Access Logic
long long block = address >> offset_bits;
int set = getSet(address, masks) % sets;

bool found = false;

for (int w = 0; w < ways; w++) {
    if (cache[set][w] == block) {
        found = true;
        hits++;
        break;
    }
}

if (!found) {
    misses++;

    bool inserted = false;

    for (int w = 0; w < ways; w++) {
        if (cache[set][w] == -1) {
            cache[set][w] = block;
            inserted = true;
            break;
        }
    }

    if (!inserted) {
        int victim = rand() % ways;
        cache[set][victim] = block;
        replacements++;
    }
}
📊 Output (stats.csv)
Row,TotalAccess,Hits,Misses,HitRate,MissRate,Utilization(%),Replacements
0,32768,25000,7768,0.76,0.24,85.5,1200
📈 Metrics Tracked
Total Accesses
Cache Hits & Misses
Hit Rate / Miss Rate
Cache Utilization (%)
Replacement Count
Set-wise Access Frequency
💡 Why This Project?
Demonstrates low-level system design
Applies bit manipulation & hashing
Simulates real-world cache behavior
Shows how custom indexing reduces conflicts
🔮 Future Improvements
Implement LRU / FIFO replacement policies
Add graph visualization
Compare with traditional indexing
Improve mask generation strategies
🧑‍💻 Tech Stack
C++ (STL)
File Handling (CSV)
Bit Manipulation
Hashing Techniques
