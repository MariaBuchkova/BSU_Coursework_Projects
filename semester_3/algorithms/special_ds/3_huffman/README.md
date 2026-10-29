# Huffman Coding

**Input file:** `huffman.in`  
**Output file:** `huffman.out`  
**Time limit:** 0.5 seconds  
**Memory limit:** 256 MB  

A greedy problem on the Huffman code: find the length of a text after Huffman encoding, knowing only the frequencies of its symbols.

## Problem

The Huffman code tree is built as follows: initially every symbol is an active vertex labeled with its frequency p_i. At each step, take the two active vertices with the **smallest labels**, create a parent labeled with the sum of their labels, and make it active instead of them. Repeat until one vertex (the root) remains. The code length of a symbol equals the length of the path from the root to its leaf.

The text itself is not given, only the frequencies of the symbols. Compute the length of the encoded text. The algorithm must work in O(n).

### Input

The first line contains an integer n (2 <= n <= 2 500 000).  
The second line contains n integers p_i — the frequencies (1 <= p_i <= 10^9, p_i <= p_(i+1)).

### Output

Output a single number — the length (in bits) of the encoded text.

## Examples

| **huffman.in** | **huffman.out** |
| :--- | :--- |
| 6<br>1 1 2 2 5 8 | 42 |

**Explanation:** the merges give `2, 4, 6, 11, 19`, and their sum is `42`.

---

## Solution & Algorithm Explanation

The problem is solved with a **greedy algorithm** and the **two queues** technique.

Each merge gives one more bit to every symbol inside the two merged vertices, so it adds their sum to the total length. Hence the answer is the **sum of the labels of all created vertices**.

The frequencies are already sorted, and the created sums come in non-decreasing order too. So instead of a heap (O(n log n)), two queues are enough: `a` for the original frequencies and `b` for the created vertices.

### How the Algorithm Works

1. Keep two pointers: `i` in `a` and `j` in `b`.
2. Repeat `n - 1` times:
   - take the smaller of the fronts `a[i]` and `b[j]` as `x`, then do the same for `y`;
   - push `x + y` to the end of `b` and add it to the answer.
3. Print the sum (stored as `long long`, since it can exceed the `int` range).

### Complexity
- **Time:** O(n).
- **Memory:** O(n).

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/special_ds/3_huffman/huffman.cpp)
- **Python implementation** — coming soon