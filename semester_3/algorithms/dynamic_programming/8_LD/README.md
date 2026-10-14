# Levenshtein Distance (String Transformation)

**Input file:** `in.txt`  
**Output file:** `out.txt`  
**Time limit:** 1 second  
**Memory limit:** No limit  

A classic dynamic programming problem on computing the minimum cost to transform one string into another using deletions, insertions, and substitutions (weighted Levenshtein distance).

## Problem

Given two non-empty character sequences `A` and `B` of length at most 1000 characters consisting of lowercase Latin letters, transform string `A` into string `B` with the minimum total penalty (cost):
- Deleting a character from string `A` costs `x` points.
- Inserting a character into string `A` costs `y` points.
- Replacing a character in string `A` with any other character costs `z` points.

### Input

- The first three lines contain positive integers `x`, `y`, and `z` respectively (not exceeding 1,000,000).
- The next two lines contain the strings `A` and `B`.

### Output

Output a single integer — the minimum total penalty for the transformation.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 2<br>3<br>1<br>abcd<br>bce | 3 |

---

## Solution & Algorithm Explanation

The problem is solved using **Dynamic Programming (DP)**, closely resembling the classic Levenshtein distance algorithm with custom weights. Note that unlike standard problems, the input and output filenames here are `in.txt` and `out.txt`.

### How the Algorithm Works

1. **Subproblems Definition:**  
   We maintain a 2D table `dp[i][j]` which stores the minimum cost to transform the prefix of string `A` of length `i` into the prefix of string `B` of length `j`.

2. **Base Cases (Initialization):**  
   - Transforming a prefix of length `i` of string `A` into an empty string requires `i` deletions: `dp[i][0] = dp[i-1][0] + x`.
   - Transforming an empty string into a prefix of length `j` of string `B` requires `j` insertions: `dp[0][j] = dp[0][j-1] + y`.

3. **State Transitions:**  
   For each character pair `A[i-1]` and `B[j-1]`:
   - If the characters match, the cost of substitution is `0`. If they don't match, the cost of replacement is `z`.
   - We take the minimum among three possible operations:
     - **Match/Substitute:** `dp[i-1][j-1] + (cost of replacement if characters differ)`
     - **Deletion from A:** `dp[i-1][j] + x`
     - **Insertion into A:** `dp[i][j-1] + y`

4. **Result:**  
   The value at `dp[A.size()][B.size()]` will hold the minimum total penalty required for the complete transformation.

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/8_LD/LD.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/8_LD/LD.py)