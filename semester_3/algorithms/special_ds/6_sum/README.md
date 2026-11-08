# Sum Problem (RSQ)

**Input:** standard input  
**Output:** standard output  
**Time limit:** 2 seconds  
**Memory limit:** 256 MB  

A classic range sum problem with point updates: maintain an array under additions to single elements and answer sum queries on half-open intervals.

## Problem

Given a sequence A of length n (0-indexed):

a_0, a_1, a_2, ..., a_(n-1).

Queries of two types arrive:

- **Add i x**: add the number x to the i-th element.
- **FindSum l r**: compute the sum of elements on the half-open interval [l, r), i.e. a_l + a_(l+1) + ... + a_(r-1), and output it.

### Input

The first line contains an integer n, the number of array elements (1 <= n <= 300 000).

The second line contains n integers a_i (-10^9 <= a_i <= 10^9).

The third line contains an integer q, the number of queries (1 <= q <= 300 000).

Each of the next q lines describes one query. A modification query is the word `Add`, then the index i (0 <= i < n) and the number x (-10^9 <= x <= 10^9). A sum query is the word `FindSum` and two indices l and r (0 <= l < r <= n), the borders of the half-open interval.

### Output

For every query of the second type, output the sum of elements on the corresponding half-open interval on a separate line.

## Examples

| **standard input** | **standard output** |
| :--- | :--- |
| 5<br>10 30 40 -10 20<br>7<br>FindSum 1 2<br>FindSum 1 3<br>FindSum 1 4<br>FindSum 3 5<br>Add 4 -10<br>FindSum 3 5<br>FindSum 0 5 | 30<br>70<br>60<br>10<br>0<br>80 |

**Explanation:** after `Add 4 -10` the array becomes 10 30 40 -10 10, so the sum on [3, 5) is 0 and the sum on [0, 5) is 80.

---

## Solution & Algorithm Explanation

This is a range sum query (RSQ) problem with point updates. The solution uses **square root decomposition**: the array is split into blocks of size k = floor(sqrt(n)), and for every block its sum is stored in a separate array `b`.

### How the Algorithm Works

1. Read the array `a` and set `k = sqrt(n)`.
2. Build the block sums: element `i` belongs to block `i / k`, so `b[i / k] += a[i]`. The number of blocks is `m = (n + k - 1) / k`.
3. **Add i x:** do `a[i] += x` and `b[i / k] += x`.
4. **FindSum l r:** let `jl = l / k` and `jr = r / k`.
   - If `jl == jr`, both ends are in one block: sum `a[l..r)` directly.
   - Otherwise sum three parts: the tail of block `jl` (elements from `l` to `(jl + 1) * k`), the whole blocks `jl + 1 .. jr - 1` through `b`, and the head of block `jr` (elements from `jr * k` to `r`).

All values are stored as `long long`, since sums can reach about 3 * 10^14 and grow further after additions.

### Complexity
- **Time:** O(n + q * sqrt(n)): O(1) per `Add`, O(sqrt(n)) per `FindSum`.
- **Memory:** O(n).

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/special_ds/6_sum/sum.cpp)
- **Python implementation** — coming soon