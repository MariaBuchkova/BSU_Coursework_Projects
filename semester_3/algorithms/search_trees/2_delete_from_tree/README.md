# Delete from Tree

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** 256 MB  

A problem on binary search trees: build a tree, delete a key using the right deletion, and print the resulting tree in pre-order.

## Problem

Given a set of keys, build a binary search tree. Delete a given key from it (using the **right deletion**) if the key is present in the tree. Then perform the pre-order left traversal (root → left subtree → right subtree) of the resulting tree.

### Input

The first line contains an integer — the key that must be deleted from the tree.  
The second line is empty.  
The following lines contain a sequence of integers — the keys of the vertices in the order they are added to the tree, one key per line. The tree contains at least two vertices.  
In a search tree all keys are unique by definition, so an attempt to add a key that is already in the tree is ignored.

### Output

Output the sequence of vertex keys obtained by the pre-order left traversal of the tree after the deletion, one key per line.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 3<br><br>2<br>3<br>1 | 2<br>1 |
| 2<br><br>4<br>2<br>1<br>3<br>5 | 4<br>3<br>1<br>5 |

**Explanation of example 2:** the tree is built from `4 2 1 3 5`: root `4`, left child `2` (with children `1` and `3`), right child `5`. The key `2` has two children, so it is replaced by the smallest key of its right subtree — `3`. After that the old vertex `3` is removed, and the pre-order traversal gives `4 3 1 5`.

---

## Solution & Algorithm Explanation

The problem is solved with a **Binary Search Tree (BST)**: keys are inserted one by one, then one key is removed with a recursive deletion, and finally the tree is printed with a **pre-order traversal**.

### Binary Search Tree property
For every vertex, all keys in its left subtree are **smaller** than its key, and all keys in its right subtree are **greater**. Deletion must keep this property true for the whole tree.

### How the Algorithm Works

1. **Reading Input:**  
   The first number `d` is the key to delete. The remaining numbers are read with `while (in >> x)` until the end of the file; the empty second line is skipped automatically by `>>`.

2. **Insertion (`add`):**  
   Each key is inserted recursively from the root: go left if `x < key`, go right if `x > key`, ignore the key if it is already in the tree. A new vertex is created when an empty place (`nullptr`) is reached.

3. **Deletion (`del`):**  
   The function searches for the key `x` going left or right according to the BST property and returns the new root of the subtree. If the key is not found (`nullptr` is reached), the tree stays unchanged. When the vertex `v` with `key == x` is found, there are three cases:
   - **No left child** — the vertex is replaced by its right child (this also covers a leaf, where the right child is `nullptr`);
   - **No right child** — the vertex is replaced by its left child;
   - **Two children (right deletion)** — find the vertex `m` with the **minimum key in the right subtree** (go right once, then left as far as possible). Copy `m->key` into `v`, then delete `m->key` from the right subtree. The BST property is preserved because `m->key` is greater than everything on the left and not greater than anything on the right.

4. **Pre-order Traversal (`preOrder`):**  
   For every vertex: print its key, then traverse the left subtree, then the right subtree. An empty subtree stops the recursion.

### Complexity
- **Time:** O(n · h) for building the tree, O(h) for the deletion and O(n) for the traversal, where `h` is the height of the tree. On average `h = O(log n)`, in the worst case (sorted input) `h = O(n)`.
- **Memory:** O(n) for the vertices; the recursion depth is O(h).

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/search_trees/2_delete_from_tree/delete_from_tree.cpp)
- **Python implementation** — coming soon