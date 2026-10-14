# Longest Increasing Subsequence (LIS)

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 to 5 seconds  
**Memory limit:** No limit  

An efficient algorithm to find the length of the longest strictly increasing subsequence in $O(n \log n)$ time using binary search.

## Problem

Given a sequence `A` consisting of `n` elements, remove the minimum number of elements so that the remaining elements form a strictly increasing subsequence. 

### Input

- The first line contains a single integer `n` ($1 \le n \le 700,000$) — the number of elements.
- The second line contains `n` integers separated by spaces (elements do not exceed $1,000,000,000$ in magnitude).

### Output

Output a single integer — the length of the longest strictly increasing subsequence.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 6<br>1 2 3 4 7 6 | 5 |

---

## Solution & Algorithm Explanation

To achieve the required $O(n \log n)$ time complexity, standard dynamic programming ($O(n^2)$) is too slow. Instead, we use a greedy approach combined with binary search.

### How the Algorithm Works

1. **Maintaining the `F` Vector:**  
   We maintain a vector `F` where `F[i]` stores the smallest ending element of all increasing subsequences of length `i + 1` found so far.
2. **Binary Search via `lower_bound`:**  
   For each element `x` from the input sequence:
   - We use `std::lower_bound` to find the first element in `F` that is greater than or equal to `x`.
   - If `x` already exists in `F`, we skip it (to handle strictly increasing condition).
   - If `x` is larger than all elements in `F` (i.e., `it == F.end()`), we append `x` to `F`, effectively extending the length of our longest increasing subsequence.
   - Otherwise, we replace the found element with `x` to keep potential future extensions as small as possible.
3. **Result:**  
   The size of the vector `F` at the end of the loop gives the exact length of the Longest Increasing Subsequence.

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/7_LIS/LIS.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/7_LIS/LIS.py)