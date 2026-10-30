# Binomial Heap

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** 64 MB  

A short problem on binomial heaps: find which binomial trees a heap with a given number of vertices consists of.

## Problem

The binomial tree B_k is defined as follows: B_0 is a single vertex, and B_k is formed by attaching the root of one B_(k-1) to the root of another B_(k-1). So B_k has 2^k vertices, and the sons of its root are the roots of B_0, B_1, ..., B_(k-1).

A binomial heap is a set of binomial trees of pairwise different heights: for every k >= 0 the tree B_k is either absent or present exactly once.

Given the total number of vertices n in a binomial heap, determine which binomial trees it can consist of.

### Input

A single number n — the number of vertices in the heap (1 <= n <= 10^18).

### Output

For every binomial tree B_k in the heap, output its height k on a separate line, in increasing order. If there are several solutions, output any. If a heap with n vertices cannot be built, output `-1`.

## Examples

| **input.txt** | **output.txt** |
| :--- | :--- |
| 13 | 0<br>2<br>3 |

**Explanation:** 13 = 2^3 + 2^2 + 2^0, so the heap consists of B_0, B_2 and B_3.

---

## Solution & Algorithm Explanation

By the property of binomial heaps, a sequence of n elements can be represented **in exactly one way** as a family of binomial trees with at most one tree of each rank: it is enough to write n as a sum of powers of two. Since B_k has 2^k vertices, the trees in the heap correspond to the **ones in the binary representation of n**. A solution always exists, so `-1` is never printed.

### How the Algorithm Works

1. Keep a counter `s = 0` — the current bit number.
2. While `n != 0`:
   - if the lowest bit is set (`n & 1`), print `s`;
   - shift `n` right by one bit (`n >>= 1`) and increase `s`.

The bits are checked from the lowest to the highest, so the heights are printed in increasing order. The number is stored as `long long`, since n can reach 10^18.

### Complexity
- **Time:** O(log n) — at most 60 shifts.
- **Memory:** O(1).

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/special_ds/2_binomial_heap/binomial_heap.cpp)
- **Python implementation** — coming soon