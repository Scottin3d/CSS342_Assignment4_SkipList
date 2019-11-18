# Skiplist
Readme 
Scott Shirley 0760484 Novemeber 2019
Notes:	1)clang tidy warnings from main, addressed in comments, did not alter given code.
	2)conducted test3() with own parameters

## Assignment
Goals: Working with dynamic arrays, pointers, doubly linked lists

For this assignment, you will write a Skip List data structure to store integers. 

When searching a Skip List, items can be found in O(log n) time. 
No duplicates are allowed.A SkipList can have multiple levels. 
SkipList of depth 1 is similar to a doubly linked list. All elements are inserted into a single doubly linked list.

When a SkipList has multiple levels, all elements are inserted at level = 0. 50% of those inserted at level = 0, 
are also inserted at level = 1. 50% of those inserted at level = 1 are also inserted at level = 2, and so on.

## Compile and Run

```
./simplecompile.sh
```

## Misc

This file is part of a repository located at
https://github.com/pisan342/ass4-skiplist-starter

