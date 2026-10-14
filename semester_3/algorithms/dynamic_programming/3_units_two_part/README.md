# Binary Strings (Parts 1 & 2)

**Input file:** `standard input`  
**Output file:** `standard output`  
**Time limit:** 1 second  
**Memory limit:** 256 MB  

A combinatorics problem on finding the number of binary strings with a given number of ones.

## Problem

Given two integers N and K, find the number of binary strings of length N that contain exactly K ones. 

Since the answer can be very large, output it modulo 10^9 + 7.

### Input

The first line of the input contains two non-negative integers N and K.
- **Part 1:** 0 <= K <= N <= 10^3
- **Part 2:** 0 <= K <= N <= 10^6

### Output

Output a single integer — the answer to the problem modulo 10^9 + 7.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 3 2 | 3 |
| 4 0 | 1 |
| 5 2 | 10 |

---

## Solution

The problem asks us to compute the binomial coefficient C(N, K) = N! / (K! * (N-K)!) modulo 10^9 + 7. Depending on the constraints, different approaches are used:

### Part 1 (N <= 10^3)
Solved using **dynamic programming** (optimizing space to O(K) by computing binomial coefficients iteratively using Pascal's identity, with symmetry optimization C(N, K) = C(N, N-K)):
- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/3_units_two_part/units1.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/3_units_two_part/units1.py)

### Part 2 (N <= 10^6)
Since N is up to 10^6, an O(N^2) DP approach is too slow. Instead, we precompute factorials up to N and use **Fermat's Little Theorem** for modular inverse:
C(N, K) = N! * (K! * (N-K)!)^(-1) (mod 10^9 + 7)

Modular inverse is computed via binary exponentiation (`fun` function) in O(log MOD) time, leading to an overall O(N + log MOD) solution.
- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/3_units_two_part/units2.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/3_units_two_part/units2.py)