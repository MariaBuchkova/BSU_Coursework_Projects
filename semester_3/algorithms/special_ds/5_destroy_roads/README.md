# Destroying Roads (Hard Version)

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1.25 seconds  
**Memory limit:** 256 MB  

A problem on disjoint set union (DSU): after each earthquake, determine whether the graph of cities is still connected. This is the hard version of the problem, with larger constraints.

## Problem

Berland has n cities connected by m roads. It is guaranteed that the graph of cities is initially connected, that is, there is a path between any pair of vertices.

q earthquakes occur in Berland, and each of them destroys exactly one road. After each earthquake it is necessary to find out whether the resulting graph of cities is connected. A destroyed road is never rebuilt, that is, it is destroyed forever.

### Input

The first line contains three integers n, m and q (1 <= n, m, q <= 750000) — the number of cities, roads and earthquakes respectively.

Each of the next m lines contains two natural numbers u and v (1 <= u, v <= n) — the cities connected by a road. It is guaranteed that u != v and that there is at most one road between any pair of cities.

Each of the next q lines contains one number x_i (1 <= x_i <= m) — the number of the road destroyed during the i-th earthquake. It is guaranteed that two different earthquakes never destroy the same road.

### Output

Output a string of length q consisting of zeros and ones. The i-th character is `1` if the graph is connected after the i-th earthquake, and `0` otherwise.

## Examples

| **input.txt** | **output.txt** |
| :--- | :--- |
| 4 6 6<br>1 2<br>2 3<br>3 4<br>4 1<br>3 1<br>4 2<br>1<br>6<br>2<br>5<br>4<br>3 | 110000 |

**Explanation:** the roads are numbered 1..6 in input order, and they are destroyed in the order 1, 6, 2, 5, 4, 3. After the 1st and 2nd earthquakes the graph is still connected (answers `1`, `1`). After the 3rd earthquake (road 2-3 is gone, together with roads 1-2 and 4-2 destroyed earlier) city 2 is isolated, so the graph is disconnected, and it stays disconnected afterwards: `110000`.

---

## Solution & Algorithm Explanation

A DSU can only **merge** sets, it cannot split them. Earthquakes **destroy** roads, so the problem is solved by **reversing time**: if we process the earthquakes from the last one to the first, destroying a road becomes adding a road, which a DSU handles easily. The solution is the same as for the simple version; only the constraints differ, so the solution has to be efficient.

### How the Algorithm Works

1. Read all m roads into arrays `eu[i]`, `ev[i]` (the ends of road `i`), so a road number immediately gives its ends in O(1).
2. Read the earthquakes `x[0..q-1]` and mark the destroyed roads: `destroyed[x[i]] = true`.
3. Build a DSU from all roads that are **never destroyed**. This is the state of the graph after all q earthquakes. Keep the counter `count` of connected components: it starts at `n` and decreases by 1 on every successful merge.
4. Go through the earthquakes **from the last to the first** (`i = q - 1 ... 0`):
   - first **record the answer**: `ans[i] = 1` if `count == 1`, otherwise `0`. This is the state of the graph right after the i-th earthquake (road `x[i]` is still destroyed, and the roads `x[i+1..q-1]` are destroyed too);
   - then **restore** road `x[i]`: find the roots of its ends, and if they differ, merge the sets and decrease `count` by 1.
5. Print the answers in the original order.

The answers are discovered from the end, but must be printed from the beginning, so they are stored in an array (or a string) first.

### DSU Storage

The DSU is stored in a single array `par`: for a non-root vertex `par[i]` is its parent, for a root it is **minus the size** of the set (a root is recognized by `par[i] < 0`). Two heuristics are used: **union by size** (the smaller tree is attached to the larger one) and **path compression** (every vertex on the search path is attached directly to the root).

### Complexity
- **Time:** O((m + q) · α(n)), where α is the inverse Ackermann function (practically a constant).
- **Memory:** O(n + m + q).

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/special_ds/5_destroy_roads/destroy_roads.cpp)
- **Python implementation** — coming soon