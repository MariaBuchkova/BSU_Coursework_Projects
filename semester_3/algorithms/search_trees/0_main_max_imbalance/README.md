# Delete the Median of the Most Unbalanced Vertices

**Input file:** `in.txt`  
**Output file:** `out.txt`  
**Time limit:** 1 second  
**Memory limit:** none  

The main assignment on binary search trees: it combines insertion, height calculation, right deletion and pre-order traversal in one problem.

## Problem

Given a binary search tree, among all its vertices find those for which the heights of the left and right subtrees differ the most. If there is a **median by key** among them, delete it from the tree (using the **right deletion**). Then perform the pre-order left traversal of the resulting tree.

If a vertex has no subtree on some side, the height of that subtree is considered equal to -1.

### Input

The input file contains a sequence of integers — the keys of the vertices in the order they are added to the tree. The tree is guaranteed to contain at least two vertices.  
In a search tree all keys are unique, so an attempt to add a key that is already in the tree is ignored.

### Output

The output file must contain the sequence of keys obtained by the pre-order left traversal of the resulting tree, one key per line.

## Examples

| **in.txt** | **out.txt** |
| :--- | :--- |
| 10<br>5<br>6<br>8<br>7<br>11<br>1<br>2<br>12<br>13<br>3 | 10<br>5<br>1<br>2<br>3<br>8<br>7<br>11<br>12<br>13 |

**Explanation:** the maximum difference of subtree heights is `2`, and it is reached in the vertices `1`, `6` and `11`. Sorted by key they form `1, 6, 11`, so the median is `6`. The vertex `6` has only a right child, so it is replaced by `8`, and the pre-order traversal gives the answer above.

---

## Solution & Algorithm Explanation

The problem is solved with a **Binary Search Tree (BST)**, a recursive calculation of subtree heights and an in-order collection of candidates.

### Key idea
An in-order traversal of a BST visits keys in **increasing order**. So if the suitable vertices are collected during an in-order traversal, they are already sorted by key, and the median is simply the middle element of the list.

### How the Algorithm Works

1. **Building the Tree (`add`):**  
   Keys are read until the end of the file and inserted recursively: left if `x < key`, right if `x > key`, duplicates are ignored.

2. **Heights and Differences (`height`):**  
   A post-order recursion returns the height of every subtree (`-1` for an empty one). For each vertex it stores `diff = |h_left - h_right|` and updates the global maximum `maxDiff`.

3. **Collecting Candidates (`collect`):**  
   An in-order traversal puts into the array `a` the keys of all vertices with `diff == maxDiff`. The keys in `a` are sorted in increasing order.

4. **Median:**  
   If the number of candidates `m` is **odd**, the median is `a[m / 2]`. If `m` is **even**, there is no median, and the tree stays unchanged.

5. **Right Deletion (`del`):**  
   The vertex with the median key is found by the BST property, then:
   - no left child — it is replaced by its right child;
   - no right child — it is replaced by its left child;
   - two children — its key is replaced by the minimum key of the right subtree, and that minimum vertex is deleted from the right subtree.

6. **Output (`preOrder`):**  
   Print the key, then traverse the left subtree, then the right subtree.

### Complexity
- **Time:** O(n · h) for building the tree, O(n) for heights, collection and traversal, O(h) for the deletion, where `h` is the height of the tree. On average `h = O(log n)`, in the worst case `h = O(n)`.
- **Memory:** O(n) for the vertices and the array of candidates; the recursion depth is O(h).

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/search_trees/0_main_max_imbalance/max_imbalance.cpp)
- **Python implementation** — coming soon