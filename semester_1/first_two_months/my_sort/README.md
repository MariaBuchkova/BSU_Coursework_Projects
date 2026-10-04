# Matrix Sorting Algorithms

A university C++ practical project focused on implementing and comparing several sorting algorithms for matrix rows.

The project was developed at an early stage of my studies, when the main goal was to understand how different sorting algorithms work and implement them manually. At that point, I was primarily focused on algorithms and data structures rather than software architecture or user interface design.

The project is intentionally kept as a simple console application and represents an early stage of my programming experience.

## Features

- Dynamic allocation of a two-dimensional matrix
- Manual matrix input or random generation
- Sorting each matrix row independently
- Ascending and descending sorting
- Manual memory management
- Console-based interaction

## Implemented Sorting Algorithms

The project includes several sorting algorithms implemented from scratch:

- **Bubble Sort**
- **Insertion Sort**
- **Counting Sort**
- **Merge Sort**

The user can select the sorting algorithm and choose the sorting direction:

- ascending
- descending

Counting Sort has an additional restriction: matrix elements must be in the range from `0` to `99`.

## Example

```text
Enter number of lines: 4 
Enter number of columns: 4
Enter the array randomly? ( 1 - true; 0 - false )
----------> 1
enter the lower limit: 0
enter the upper limit: 10

   8   0   8   0
   1   1   2   0
   2   4  10   7
   6   4   4   0
   
How would you like to sort? (Enter 0 if descending, 1 if ascending): 1

Select how you want to sort the lines:
Enter 1 - bubble
Enter 2 - insert
Enter 3 - count (only possible for numbers from 0 to 99)
Enter 4 - merge
enter an option: 3

count sort matrix:
   0   0   8   8
   0   1   1   2
   2   4   7  10
   0   4   4   6