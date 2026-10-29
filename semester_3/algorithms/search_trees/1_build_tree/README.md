# Build a Tree

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** 256 MB  

A basic problem on binary search trees: insert keys one by one and print the tree in pre-order (root, left subtree, right subtree).

## Problem

Given a set of keys, build a binary search tree and perform its pre-order left traversal (root → left subtree → right subtree).

### Input

The input file contains a sequence of integers — the keys of the vertices in the order they are added to the tree. Keys are given one per line.  
In a search tree all keys are unique by definition, so an attempt to add a key that is already in the tree is ignored.

### Output

The output file must contain the sequence of vertex keys obtained by the pre-order left traversal of the tree, one key per line.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 2<br>3 | 2<br>3 |
| 5<br>2<br>4<br>1<br>8<br>7 | 5<br>2<br>1<br>4<br>8<br>7 |
| 0<br>100<br>-100 | 0<br>-100<br>100 |

**Explanation of example 2:** `5` becomes the root. `2 < 5` goes to the left, `4` goes left of `5` and then right of `2`, `1` goes left of `2`, `8` goes right of `5`, and `7` goes left of `8`. The pre-order traversal visits `5`, then the left subtree (`2`, `1`, `4`), then the right subtree (`8`, `7`).

---

## Solution & Algorithm Explanation

The problem is solved with a **Binary Search Tree (BST)** and a recursive **pre-order traversal**.

### Binary Search Tree property
For every vertex, all keys in its left subtree are **smaller** than its key, and all keys in its right subtree are **greater**. This property is what makes insertion and search fast, and it is also why duplicates have no place in the tree.

### How the Algorithm Works

1. **Vertex Structure:**  
   Each vertex stores its `key` and two pointers: `l` (left child) and `r` (right child). A missing child is `nullptr`.

2. **Insertion (`add`):**  
   Keys are read from the file one by one and inserted recursively starting from the root:
   - if the current vertex is `nullptr`, create a new vertex with this key and return it;
   - if `x < key`, go into the left subtree;
   - if `x > key`, go into the right subtree;
   - if `x == key`, do nothing — the duplicate is ignored.

   The function returns the (possibly new) subtree root, so the parent simply re-assigns its child pointer: `v->l = add(v->l, x)`.

3. **Reading Input:**  
   The number of keys is not given, so the file is read with `while (in >> x)` until it ends. The first key becomes the root.

4. **Pre-order Traversal (`preOrder`):**  
   For every vertex, in this exact order:
   - print the vertex key;
   - traverse the left subtree;
   - traverse the right subtree.

   An empty subtree (`nullptr`) stops the recursion.

### Complexity
- **Time:** O(n · h) for building the tree and O(n) for the traversal, where `h` is the height of the tree. On average `h = O(log n)`, in the worst case (keys given in sorted order) the tree degenerates into a chain and `h = O(n)`.
- **Memory:** O(n) for the vertices; the recursion depth is O(h).

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/trees/build_tree/build_tree.cpp)
- **Python implementation** — coming soon