# Longest Common Subsequence (LCS)

**Input file:** `standard input`  
**Output file:** `standard output`  
**Time limit:** 2 seconds  
**Memory limit:** 64 MB  

A classic dynamic programming problem on finding the longest common subsequence between two sequences along with the exact index reconstructions.

## Problem

Given two sequences A and B, each of length n, find the maximum length k and the corresponding sequences of indices (i_1 < i_2 < ... < i_k) and (j_1 < j_2 < ... < j_k) such that elements at these positions are equal: A[i_1] = B[j_1], A[i_2] = B[j_2], and so on.

### Input

- The first line contains a single integer n (1 <= n <= 1000) — the length of sequences A and B.
- The second line contains n integers — elements of sequence A (1 <= a_i <= 1000).
- The third line contains n integers — elements of sequence B (1 <= b_j <= 1000).

### Output

- In the first line, output the length of the longest common subsequence k.
- In the second line, output the indices in sequence A.
- In the third line, output the indices in sequence B.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 2<br>1 2<br>1 2 | 2<br>0 1<br>0 1 |
| 5<br>1 2 3 4 5<br>1 3 2 4 4 | 3<br>0 1 3<br>0 2 4 |

---

## Solution & Algorithm Explanation

The problem is solved using **Dynamic Programming (DP)** followed by **backtracking** for path reconstruction.

### How the Algorithm Works

1. **Subproblems Definition (dp table):**  
   We create a 2D table `dp` of size (k+1) x (k+1), where `dp[i][j]` stores the length of the Longest Common Subsequence for the prefix of sequence A of length i and sequence B of length j.

2. **State Transitions (Filling the Table):**  
   We iterate through elements of both sequences:
   - If the current elements match (`A[i-1] == B[j-1]`), we extend the common subsequence from the previous elements: `dp[i][j] = dp[i-1][j-1] + 1`.
   - If they don't match, we take the maximum possible length by omitting either the current element of A or the current element of B: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.

3. **Reconstructing the Indices (Backtracking):**  
   Starting from the bottom-right corner of our DP table (`i = k`, `j = k`), we move backwards:
   - If `A[i-1] == B[j-1]`, it means this element is part of the optimal LCS. We record its 0-based indices and move diagonally up-left (`i -= 1`, `j -= 1`).
   - Otherwise, we move in the direction of the larger value in the adjacent cells (`dp[i-1][j]` or `dp[i][j-1]`) to trace back which element was skipped.
   - Finally, we reverse the collected index lists to output them in increasing order.

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/5_LCS/LCS.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/5_LCS/LCS.py)