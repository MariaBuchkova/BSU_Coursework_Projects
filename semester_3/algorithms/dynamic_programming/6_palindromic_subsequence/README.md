# Longest Palindromic Subsequence

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** No limit  

A classic dynamic programming problem on finding the longest palindromic subsequence by reducing it to the Longest Common Subsequence (LCS) problem.

## Problem

Given a non-empty string `S` of length at most 7000 characters consisting only of lowercase Latin letters, remove the minimum number of characters to form a palindrome (a string that reads the same forwards and backwards).

### Input

The first line contains the initial string `S`.

### Output

- In the first line, output the length of the resulting palindrome.
- In the second line, output the palindrome itself (if there are multiple palindromic subsequences, any valid one can be output).

## Examples

| **Input** | **Output** |
| :--- | :--- |
| asddfsa | 6<br>asddsa |

---

## Solution & Algorithm Explanation

This problem is a direct extension/application of the **Longest Common Subsequence (LCS)** problem.

### How it builds on LCS
1. **Reduction to LCS:**  
   If we take the original string `A` and create its reversed copy `B`, the Longest Common Subsequence between `A` and `B` will give us the Longest Palindromic Subsequence of the original string!
2. **DP Table and Backtracking:**  
   We build the standard 2D `dp` table of size `(k+1) x (k+1)` to find the LCS between the string and its reverse. Then, we use backtracking to reconstruct the exact characters forming the palindrome.

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/6_palindromic_subsequence/palindromic_subsequence.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/6_palindromic_subsequence/palindromic_subsequence.py)