# Is the Binary Tree a Search Tree?

**Input file:** `bst.in`  
**Output file:** `bst.out`  
**Time limit:** 1 second  
**Memory limit:** 64 MB  

A problem on binary trees: check whether a given tree satisfies the binary search tree property, allowing equal keys.

## Problem

A binary tree is given. Determine whether it is a binary search tree. The tree **may contain equal keys**, so for every vertex x all keys in the left subtree must be **strictly less** than the key of x, and all keys in the right subtree must be **greater than or equal** to it.

### Input

The first line contains an integer n (1 <= n <= 8 * 10^5) — the number of vertices.  
The next line contains the key of the root (-2^31 <= m <= 2^31 - 1).  
Each of the following n - 1 lines contains `m p c`:
- m — the key of the vertex;
- p — the number of the line where the parent was given (lines are numbered from zero, p is less than the current line number);
- c — `L` if the vertex is the left child of its parent, `R` if it is the right one.

The lines describe a correct binary tree.

### Output

Output `YES` if the tree is a binary search tree, and `NO` otherwise.

## Examples

| **bst.in** | **bst.out** |
| :--- | :--- |
| 7<br>1<br>2 1 L<br>4 2 L<br>3 1 R<br>5 2 R<br>6 4 L<br>7 4 R | NO |

**Explanation:** the left child of the root `1` has key `2`, but keys in the left subtree must be strictly less than `1`.

---

## Solution & Algorithm Explanation

The idea is to pass an **allowed range of keys** `[lo, hi]` from the root down to every vertex.

Comparing a vertex only with its parent is not enough: a key must fit the limits of **all** its ancestors, so each vertex keeps the whole range.

### How the Algorithm Works

1. **Root:** its range is `[LLONG_MIN, LLONG_MAX]`.
2. **Children:** a parent always comes before its children, so vertices are processed in input order. For a parent `par`:
   - left child: range `[par->lo, par->key - 1]` (strictly less);
   - right child: range `[par->key, par->hi]` (greater or equal).
3. **Check:** if `key < lo` or `key > hi`, the tree is not a search tree.
4. **Answer:** `YES` if no vertex violated its range, otherwise `NO`.

Values are stored as `long long`, so `key - 1` and the bounds never overflow.

### Complexity
- **Time:** O(n).
- **Memory:** O(n). No recursion is used, so a degenerate tree causes no stack overflow.

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/search_trees/3_is_bst/is_bst.cpp)
- **Python implementation** — coming soon