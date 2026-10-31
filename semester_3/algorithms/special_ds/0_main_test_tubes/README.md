# Chemical Reaction

**Input file:** `in.txt`  
**Output file:** `out.txt`  
**Time limit:** 1 second  
**Memory limit:** not specified  

A short problem on the stack: simulate substances being added to a test tube one by one, where neighbouring substances may react with each other.

## Problem

A matrix A of size n × n describes the results of chemical reactions between substances. The substances are numbered from 1 to n. The element a_ij is the number of the substance obtained as a result of the reaction of substance i with substance j (if the substances do not react, then a_ij = 0).

There is a test tube into which some substances are added one after another. Substance i reacts with substance j if it is located in the test tube directly above it. If the substances do not react, they do not mix in the test tube.

It is necessary to determine which substances, and in what order, will be in the test tube after all the substances have been added.

### Input

The first line contains the number n of distinct substances (1 <= n <= 300) and the number m (1 <= m <= 1 000 000) of added substances.

Each of the next n lines contains the elements of the corresponding row of the matrix. The matrix is guaranteed to be symmetric (a_ij = a_ji for all i, j), and identical substances do not react with each other but mix (a_ii = i for all i).

The last line contains m numbers, the numbers of the substances, in the order in which they were added to the test tube.

### Output

A single line with the numbers of the substances that ended up in the test tube, starting from the top level and ending with the bottom level.

## Examples

| **in.txt** | **out.txt** |
| :--- | :--- |
| 3 4<br>1 3 2<br>3 2 1<br>2 1 3<br>1 3 1 2 | 1 |
| 5 6<br>1 3 0 2 0<br>3 2 0 1 3<br>0 0 3 5 1<br>2 1 5 4 0<br>0 3 1 0 5<br>1 3 2 4 5 1 | 1 5 1 3 1 |

**Explanation (first example):** add 1: the tube is [1]. Add 3: it reacts with 1 and gives a_13 = 2, so the tube is [2]. Add 1: it reacts with 2 and gives a_21 = 3, so the tube is [3]. Add 2: it reacts with 3 and gives a_32 = 1, so the tube is [1]. The answer is `1`.

**Explanation (second example):** 1 gives [1]; 3 does not react with 1 (a_13 = 0), giving [1, 3]; 2 does not react with 3, giving [1, 3, 2]; 4 reacts with 2 and gives 1, which does not react with 3 (a_31 = 0), giving [1, 3, 1]; 5 does not react, giving [1, 3, 1, 5]; 1 does not react with 5, giving [1, 3, 1, 5, 1]. Read from the top: `1 5 1 3 1`.

---

## Solution & Algorithm Explanation

The test tube behaves exactly like a **stack**: new substances are added on top, and a new substance can react only with the one lying directly under it, that is, with the top of the stack. The result of a reaction replaces both substances, and it can then react again with the next substance below.

### How the Algorithm Works

1. Read the matrix `a` and keep an empty stack `st`.
2. For every added substance `x`:
   - while the stack is not empty and `a[top][x] != 0` (the substances react): take `top` off the stack and replace `x` with the reaction result `a[top][x]`;
   - push `x` onto the stack.
3. After all substances have been added, print the stack **from the top to the bottom**, with a single space between numbers and no trailing space.

The `while` loop is important: after a reaction the new substance may react again with the next substance in the stack (a chain reaction).

### Indexing

Substances are numbered from 1, while the matrix is stored from 0, so it is accessed as `a[top - 1][x - 1]`.

### Complexity
- **Time:** O(n^2 + m) — reading the matrix plus one pass over the substances; every substance is pushed onto the stack once and popped at most once.
- **Memory:** O(n^2 + m) — the matrix and the stack.

### Implementation

- [**C++ implementation**](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/special_ds/0_main_test_tubes/test_tubes.cpp)
- **Python implementation** — coming soon