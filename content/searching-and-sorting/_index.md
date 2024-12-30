---
title: "Searching And Sorting Problems"
weight: 1
---
# Searching and Sorting

To understand this type of problem, we need to consider cases where a specific permutation of the `array` or `vector` might be beneficial for us. If such a permutation has the characteristic that its elements are ordered monotonically, we can implement a sorting algorithm to achieve this order. 

When it comes to the searching phase, it's important to note that scanning an `array` of size `n` in the worst case takes $O(n)$ time. For large constraints, such as an `array` of size $10^9$, this becomes computationally infeasible, as scanning such an `array` empirically takes more than `1 second`. Generally, if a solution takes too long to execute, it results in an error commonly known as `TLE` (Time Limit Exceeded).

## Table of Contents
- [easy sort problem](easy-sort-problem)