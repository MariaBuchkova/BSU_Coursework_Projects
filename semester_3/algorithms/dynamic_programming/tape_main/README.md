# Tape (Лента)

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** none  

A classic two-player game on a tape, solved with interval dynamic programming (minimax).

## Problem

A tape of width one cell and length n cells is given. Each cell contains an integer. Two players move in turns. In one move a player cuts off one of the end cells of the tape and takes it. The game ends when the tape is empty. A player's score is the sum of the numbers in the cells they have taken.

Determine the score that the player who moves first can guarantee for himself, i.e. the score he is able to secure against **any** play of the second player.

### Input

The first line contains a single integer n — the length of the tape (1 <= n <= 1000).  
The second line contains n integers — the numbers on the tape, separated by spaces.

### Output

Output a single integer — the guaranteed score of the player who starts the game.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 3<br>1 3 4 | 5 |
| 4<br>4 2 10 1 | 14 |

**Explanation of example 1:** the first player takes `1`, the second player then chooses between `3` and `4`. If he takes `4`, the first player gets `3` (total `1 + 3 = 4`); if he takes `3`, the first player gets `4` (total `1 + 4 = 5`). The second player picks the worse option for the first one, so taking `1` guarantees only `4`. Taking `4` first leaves `1 3`: the opponent takes `3`, and the first player gets `1`, total `5`. So the answer is `5`.

---

## Solution & Algorithm Explanation

The problem is solved using **Dynamic Programming (DP)** over segments of the tape.

### Why greedy approaches fail
Always taking the larger end cell is not optimal: grabbing a big number may open an even bigger one for the opponent. Because the opponent plays optimally too, we have to look ahead and evaluate both possible moves in every position.

### How the Algorithm Works

1. **State Definition:**  
   Any position of the game is a contiguous segment `[i, j]` of the original tape. For every segment we store two values in one table `f`:
   - `f[i][j]` (for `i <= j`) — the best score the player can guarantee **if he moves first** on segment `[i, j]`;
   - `f[j][i]` (for `i < j`, the mirrored cell below the diagonal) — the score this player gets **if the opponent moves first** on segment `[i, j]`.

   Using the second half of the table for the "opponent moves first" case lets us keep everything in a single `n x n` array.

2. **Base Case:**  
   A segment of length 1: `f[i][i] = a[i]` (the only cell is taken by whoever moves). For a segment of length 2 the first mover simply takes the larger number, the other gets the smaller one:
   - `f[i][j] = max(a[i], a[j])`
   - `f[j][i] = min(a[i], a[j])`

3. **Building up by Length (Bottom-Up):**  
   We process segments in order of increasing length, from 3 up to `n`, so all shorter segments are already computed.

4. **Transitions for segment `[i, j]`:**
   - **Player moves first** — he takes the left cell `a[i]` or the right cell `a[j]`, and then the opponent moves first on the remaining segment:
     `f[i][j] = max(a[i] + f[j][i+1], a[j] + f[j-1][i])`
   - **Opponent moves first** — the opponent takes one end, and then our player moves first on what remains. The opponent chooses the option that is worse for us:
     `f[j][i] = min(f[i+1][j], f[i][j-1])`

5. **Answer:**  
   The result is `f[0][n-1]` — the guaranteed score of the first player on the whole tape.

### Complexity
- **Time:** O(n²) — each of the O(n²) segments is computed in O(1).
- **Memory:** O(n²) for the table `f`.

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/dynamic_programming/tape_main/tape.cpp)
- **Python implementation** — coming soon