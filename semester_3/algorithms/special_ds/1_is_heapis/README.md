# Is It a Heap?

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** 256 MB  

A basic problem on the heap data structure: check whether an array can represent a binary min-heap.

## Problem

A complete binary tree on n vertices can be stored in an array of length n: indexing starts from one, and the element with index i has as its sons the elements with indices 2i and 2i + 1 (if they exist).

A binary heap is a complete binary tree in which the priority of any vertex is not lower than the priority of each of its sons. The element with the **smaller** key has the higher priority (**Min-Heap**).

Determine whether the given array can represent a binary heap. Special checking methods from standard libraries (such as `std::is_heap`) are **forbidden**.

### Input

The first line contains the number n of elements (1 <= n <= 100 000).  
The second line contains n space-separated integers, each not exceeding 10^9 in absolute value.

### Output

Output `Yes` if the array represents a binary heap, and `No` otherwise.

## Examples

| **input.txt** | **output.txt** |
| :--- | :--- |
| 10<br>9 17 16 25 21 20 60 25 40 33 | Yes |

**Explanation:** every element is not greater than its sons, for example `9 <= 17, 16` and `17 <= 25, 21`.

---

## Solution & Algorithm Explanation

The shape of a complete binary tree is fully determined by the array, so it is enough to check the **Min-Heap property**: no element is greater than its children.

### How the Algorithm Works

1. **Indexing:** the code counts from zero, so the children of `i` are `2i + 1` and `2i + 2` (the same rule as `2i` and `2i + 1` from one).
2. **Check:** go through all elements that have a child (`2i + 1 < n`). If `a[i] > a[l]`, or the right child exists and `a[i] > a[r]`, the answer is `No`.
3. **Equal keys** are allowed, because only a strictly greater parent breaks the property.
4. **Answer:** `Yes` if no violation was found.

### Complexity
- **Time:** O(n).
- **Memory:** O(n).

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/special_ds/1_is_heap/is_heap.cpp)
- **Python implementation** — coming soon