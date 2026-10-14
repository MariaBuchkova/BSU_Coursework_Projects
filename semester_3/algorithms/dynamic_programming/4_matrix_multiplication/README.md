# Matrix Chain Multiplication

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** 256 MB  

A classic dynamic programming problem on finding the optimal order of matrix multiplications to minimize the number of scalar operations.

## Problem

Given a sequence of s matrices A1, A2, ..., As, determine the optimal parenthesis placement (multiplication order) that minimizes the total number of atomic multiplication operations. 

Multiplying a k x m matrix by an m x n matrix takes k * m * n operations and results in a k x n matrix. Matrix multiplication is associative, so the final resulting matrix remains the same regardless of the order of operations.

### Input

The first line of the input contains a single integer s — the number of matrices (2 <= s <= 100).  
The subsequent s lines contain the dimensions of the matrices: the (i + 1)-th line contains the number of rows ni and the number of columns mi for matrix Ai (1 <= ni, mi <= 100).  
It is guaranteed to be compatible: mi = ni+1 for all 1 <= i <= s-1.

### Output

Output a single integer — the minimum number of scalar operations required to multiply the s matrices.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 3<br>2 3<br>3 5<br>5 10 | 130 |
| 4<br>20 5<br>5 35<br>35 4<br>4 25 | 3100 |

---

## Solution & Algorithm Explanation

The problem is solved using **Dynamic Programming (DP)**. 

### Why greedy approaches fail
Matrix multiplication is associative (`(A * B) * C` gives the same result as `A * (B * C)`), but the number of operations can differ drastically. A greedy choice (always picking the cheapest local multiplication first) doesn't guarantee a global minimum, so we need to check all possible ways to group the matrices.

### How the Algorithm Works

1. **Subproblems Definition:**  
   We define a 2D table `a[i][j]` which stores the minimum number of operations needed to multiply the chain of matrices starting from index `i` up to index `j`.

2. **Building up by Length (Bottom-Up):**  
   We solve smaller subproblems first (chains of length 2, then 3, and so on up to length `s`). 
   - For a chain from `i` to `j`, we try every possible split point `k` (where `i <= k < j`). 
   - This splits the chain into two independent sub-chains: `from i to k` and `from k+1 to j`.

3. **Cost Calculation at Split Point `k`:**  
   The total cost for a specific split point `k` consists of three parts:
   - The cost to compute the left sub-chain (`a[i][k]`)
   - The cost to compute the right sub-chain (`a[k+1][j]`)
   - The cost of multiplying the resulting two big matrices together: `(rows of left part) * (columns of left part / rows of right part) * (columns of right part)`. In terms of dimensions array, this is `size[i * 2] * size[k * 2 + 1] * size[j * 2 + 1]`.

4. **Optimizing:**  
   We iterate through all possible split points `k` for a given range `(i, j)` and pick the minimum possible value to update `a[i][j]`. 

By the end of the algorithm, `a[0][n-1]` will hold the absolute minimum operations needed for the entire sequence.

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/4_matrix_multiplication/matrix_multiplication.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/4_matrix_multiplication/matrix_multiplication.py)