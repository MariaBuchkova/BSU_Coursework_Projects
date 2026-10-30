# Building Roads

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** 256 MB  

A short problem on disjoint set union (DSU): after each added road, find the number of connected components.

## Problem

Berland consists of $n$ cities. Initially all cities are isolated, that is, there are no roads between them.

Roads between pairs of cities are added one by one. After each added road, it is necessary to find the number of connected components in the graph of cities.

## Input

The first line contains two integers $n$ and $q$ ($1 \le n, q \le 500000$) — the number of cities and the number of queries.

Each of the next $q$ lines contains two integers $u$ and $v$ — between which pair of cities a road is built. At most one road is built between any pair of cities, and $u \ne v$ for every query.

## Output

After each added road, output one number — the current number of connected components in the graph of cities.

## Examples

| input.txt | output.txt |
| :--- | :--- |
| 5 5<br>1 2<br>3 4<br>1 3<br>3 5<br>1 5 | 4<br>3<br>2<br>1<br>1 |

**Explanation:** initially there are 5 components. Road 1-2 merges two of them (4 left), road 3-4 gives 3, road 1-3 merges {1, 2} and {3, 4} (2 left), road 3-5 joins city 5 (1 left), and road 1-5 connects cities that are already in the same component, so the answer stays 1.

## Solution & Algorithm Explanation

The problem is solved with a disjoint set union (DSU). Each component is a set of cities reachable from each other, and the number of components changes only when two different sets are merged.

### How the Algorithm Works

1. Initially every city is its own one-element set, so the counter is `count = n`.
2. For each road (`u`, `v`):
   * find the representatives (roots) `pu = FindSet(u)` and `pv = FindSet(v)`;
   * if `pu == pv`, the cities are already connected, and the number of components does not change;
   * if `pu != pv`, merge the two sets with `Union` and decrease `count` by 1.
3. Print `count` after every query.

### DSU Storage

The DSU is stored as a family of rooted trees in a single array `par` (a compact variant of “Method 2” from the lecture):

* for a non-root vertex `i`, `par[i]` is its parent;
* for a root, `par[i]` is **negative**: it equals minus the size of the set. A root is recognized by `par[i] < 0`.

Two heuristics are used:

* **Union by size:** the root of the smaller tree is attached to the root of the larger one. With sizes stored as negative numbers, “larger” means a smaller value of `par`. This keeps the tree height at most $\log_2(n)$.
* **Path compression:** during `FindSet` every vertex on the search path is attached directly to the root.

### Complexity

* **Time:** $\mathcal{O}((n + q) \cdot \alpha(n))$, where $\alpha$ is the inverse Ackermann function (practically a constant, $\alpha(n) \le 4$).
* **Memory:** $\mathcal{O}(n)$.

## Implementation

* [C++ implementation](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/special_ds/4_build_roads/build_roads.cpp)
* Python implementation — coming soon