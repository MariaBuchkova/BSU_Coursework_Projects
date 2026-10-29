# Dynamic Programming

A collection of practical assignments focused on **Dynamic Programming** as part of the university Algorithms course.

## Future Work

### 🔹 [tape_main](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/tape_main)

**Task:** on a tape of \(n\) cells, two players take turns cutting off one of the end cells and taking its number. Find the maximum score the first player can guarantee against any play of the opponent.

**Approach:**
- **Interval Dynamic Programming (minimax)** — for every segment, store the best score when the player moves first and the score he gets when the opponent moves first. Complexity: O(n²).

### 🔹 [3_units_two_part](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/3_units_two_part)

**Task:** count the binary strings of length \(n\) that contain exactly \(k\) ones.

**Approaches:**
- **Dynamic Programming** — build Pascal's triangle to get the number of valid arrangements.
- **Binary Exponentiation** — compute the binomial coefficient via factorials and modular inverses.

### 🔹 [6_palindromic_subsequence](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/6_palindromic_subsequence)

**Task:** find the **Longest Palindromic Subsequence (LPS)** of a given sequence. A subsequence keeps the relative order of elements, and a palindrome reads the same forward and backward.

**Approach:**
- **Dynamic Programming** over segments to determine the maximum possible length.

## Assignments

| **Task** | **Description** |
| --- | --- |
| [tape_main](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/tape_main) | Finding the maximum score the first player can guarantee in a two-player game on a tape using interval dynamic programming. |
| [0_task00](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/0_task00) | Introductory assignment covering the fundamentals of algorithmic problem solving. |
| [1_binary_search](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/1_binary_search) | Searching for a target element in a sorted sequence using binary search. |
| [2_frog](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/2_frog) | Finding an optimal path for a frog while minimizing the total cost. |
| [3_units_two_part](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/3_units_two_part) | Counting binary strings of length \(n\) containing exactly \(k\) ones using dynamic programming and binary exponentiation. |
| [4_matrix_multiplication](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/4_matrix_multiplication) | Matrix multiplication and related algorithmic operations. |
| [5_LCS](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/5_LCS) | Finding the Longest Common Subsequence (LCS) of two sequences. |
| [6_palindromic_subsequence](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/6_palindromic_subsequence) | Finding the Longest Palindromic Subsequence (LPS) using dynamic programming. |
| [7_LIS](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/7_LIS) | Finding the Longest Increasing Subsequence (LIS) in a sequence. |
| [8_LD](https://github.com/MariaBuchkova/BSU_Coursework_Projects/tree/main/semester_3/algorithms/dynamic_programming/8_LD) | Additional assignment related to dynamic programming. |

## Technologies

- C++
- Dynamic Programming
- Algorithms and Data Structures
- Problem Solving