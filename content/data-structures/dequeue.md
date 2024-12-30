---
title: "Dequeue"
---

# Dequeue

## What's a dequeue?

Is a generalize version of a queue with double Ended, where we can insert and delete elements at boths sides.

So, in any problem when we need to pop or push elements fast on $O(1)$ this data structure is very util.

## Problem - find longest special substring that occurs thrice I
You are given a string `s` that consists of lowercase English letters.

A string is called *special* if its made up of only a single character. For example, the string `abc` is not special, whereas the string `ddd`, `zz` and `f` are special.

Return the length of the longest special substrings of `s` which occurs at least thrice, or `-1` if no special substring occurs at least thrice.

A substrings is a contiguous non-empty sequence of characters within a string.

### Example test case 1:
Input: `s = "aaaa"`
Output: `2`

Explanation: 
* If $k = 1$, so i have `{{a}, {a}, {a}, {a}}`, and repeat more than 3 times. Its a factible answer.
* If $k = 2$, so i have `{{aa}, {aa}, {aa}}`, and repeat more than 3 times. Its a factible answer and the best at moment.
* If $k = 3$, so i have `{{aaa}, {aaa}}`, and repeat more than 3 times. Its not a factible answer.


### Thoughts
* The substring must be contiguous and non-empty, so the combinations should consist of adjacent characters.
* If I need to calculate combinations of adjacent characters in a string, perhaps I can use a sliding window approach.
* However, with a sliding window, if I want to pop or push characters from the front or end of my temporary contiguous substrings of size `k`, the time complexity will increase if I try to insert elements at the front.
* Keep in mind that the `+=` operation on a string creates a copy of the object, which uses both time and memory.
* To efficiently track the characters in my window, I can use a `deque<char>` for fast popping and pushing.


## References:
* link to the original problem: https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/description/