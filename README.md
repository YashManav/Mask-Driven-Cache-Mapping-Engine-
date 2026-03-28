# 🧠 Cache Simulator Project

A high-performance **Cache Simulator** built using **C++** to model memory access behavior and analyze cache performance under different configurations.

---

## 📌 Overview

This project simulates how cache memory works by processing memory access traces and applying different cache mapping and replacement strategies. It helps in understanding **cache hits, misses, and overall system efficiency**.

---

## ⚙️ Features

* Customizable cache parameters:

  * Cache Size
  * Block Size
  * Associativity

* Supports cache mapping techniques:

  * Direct Mapping
  * Set-Associative Mapping
  * Fully Associative Mapping

* Trace file generation

* Address mask generation

* Detailed performance metrics

---

## 🏗️ Project Structure

```bash
Cache-Simulator/
│── trace_Generator.cpp      # Generates memory access traces
│── mask_Generator.cpp       # Generates masks for tag/index/offset
│── hashfunc.cpp             # Main simulation logic
│── README.md                # Project documentation
```

---

## 🚀 Getting Started

### 1️⃣ Compile the Code

```bash
g++ trace_Generator.cpp -o traceGen
g++ mask_Generator.cpp -o maskGen
g++ hashfunc.cpp -o simulator
```

---

### 2️⃣ Run the Programs

```bash
./traceGen
./maskGen
./simulator
```

---

## 🧩 Core Concepts

### 🔸 Cache Address Breakdown

Each memory address is divided into three parts:

* **Tag** → Identifies the block
* **Index** → Selects the cache line/set
* **Offset** → Identifies data within the block

---

### 🔸 Hash Function (Parity Example)

```cpp
int parity(long long x) {
    int p = 0;
    while (x) {
        p ^= (x & 1);
        x >>= 1;
    }
    return p;
}
```

---

## 📊 Output Metrics

The simulator provides:

* Total Memory Accesses
* Cache Hits
* Cache Misses
* Hit Ratio
* Miss Ratio

---

## 📊 Sample Output

```text
Total Accesses: 1000
Cache Hits: 720
Cache Misses: 280
Hit Ratio: 72%
Miss Ratio: 28%
```

---

## 🛠️ Customization

You can modify cache behavior by editing parameters in:

```bash
cacheSimulator.cpp
```

Options include:

* Cache size
* Block size
* Associativity
* Replacement policy

---

## 📄 License

This project is open-source and available under the **MIT License**.
