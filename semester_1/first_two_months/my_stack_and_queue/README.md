# Stack and Queue

A university C++ practical project focused on implementing basic linear data structures from scratch.

The project contains custom implementations of a **stack** and two types of **queues**, using dynamically allocated arrays and linked lists.

The main goal of the assignment was to understand how these data structures work internally and implement their basic operations without using the corresponding standard library containers.

## Implemented Data Structures

### Stack

Two stack implementations are included:

* `StackArr` — stack based on a dynamically allocated array
* `stackList` — stack based on a linked list

Supported operations include:

* `push`
* `pop`
* checking whether the stack is empty or full
* getting the top element
* clearing the stack
* getting the current size

### Queue

Two array-based queue implementations are included:

* `CyclicQueueArr` — circular queue using a fixed-size array
* `LinearQueueArr` — linear queue using a fixed-size array

Supported operations include:

* `push`
* `pop`
* `front`
* `back`
* checking whether the queue is empty or full
* clearing the queue
* getting the current size
* printing the elements

## Implementation Details

The project demonstrates manual memory management using dynamic arrays and pointers.

The linked-list stack uses dynamically allocated nodes connected through pointers. The circular queue uses modular arithmetic to reuse positions at the beginning of the array after elements are removed.

## Project Context

This was an early university practical assignment focused primarily on understanding the internal implementation of basic data structures.

The project is intentionally kept simple and uses a console-based implementation. The main purpose was to practice **pointers, dynamic memory management, linked lists, stacks, queues, and their basic operations**, rather than application architecture or interface development.

## Technologies

* C++
* Data Structures
* Dynamic Memory Management
* Linked Lists
* Dynamic Arrays
