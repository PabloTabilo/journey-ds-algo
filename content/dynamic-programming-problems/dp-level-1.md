---
title: "DP Level 1"
weight: 1
---
# DP Level 1
Let’s dive into this LeetCode problem to uncover the foundational concepts of dynamic programming. Together, we’ll explore the key techniques and data structures specific to DP that will help you approach and solve it effectively.

## 2466. Count Ways To Build Good Strings
* Level `medium`.

### Problem statement
Given the integers `zero`, `one`, `low`, and `high`, we can construct a string by starting with an empty string, and then at each step perform either of the following:

* Append the character '0' `zero` times.
* Append the character '1' `one` times.
This can be performed any number of times.

A good string is a string constructed by the above process having a length between low and high (inclusive).

Return the number of different __good strings__ that can be constructed satisfying these properties. Since the answer can be __large__, return it modulo $10^9 + 7$.

#### Example 1:
```
Input: low = 3, high = 3, zero = 1, one = 1
Output: 8
```
Explanation: 

* One possible valid good string is "011". 
* It can be constructed as follows: "" -> "0" -> "01" -> "011". 
* All binary strings from "000" to "111" are good strings in this example.

#### Example 2:
```
Input: low = 2, high = 3, zero = 1, one = 2
Output: 5
```
Explanation: 
* The good strings are "00", "11", "000", "110", and "011".
 

#### Constraints:
* $1 \le low \le high \le 10^5$
* $1 \le zero, one \le low$

### First Thoughts
My first approach was a recursive solution because, for me, it’s more intuitive to visualize the relationship and structure between the branches of each node.
Here’s the code:
```cpp
class Solution {
public:
    int low, high, zero, one;
    int ans = 0;
    void f(int sz, string& s){
        if(sz >= low && sz <= high){
            cout <<"permutation:" << s << endl;
            ans++;
        }
        if(sz > high){
            return;
        }

        for(int k=1;k<=zero;k++) s.push_back('0');
        
        f(sz+zero, s);

        for(int k=1;k<=zero;k++) s.pop_back();
        
        
        for(int k=1;k<=one;k++) s.push_back('1');
        
        f(sz+one, s);

        for(int k=1;k<=one;k++) s.pop_back();
        
    }
    int countGoodStrings(int low, int high, int zero, int one) {
        this->low = low;
        this->high = high;
        this->zero = zero;
        this->one = one;
        string permutation = "";
        f(0, permutation);
        return ans;
    }
};
```
* The code works, but the time complexity is terrible, around $O(2^n)$. Also, don’t forget that for each node, I add a `char` (either `one` or `zero` times) to a string for debugging purposes.
* The first thing to notice is that the structure of the solution is consistent (__same__), which is why I can use a `f(sz)` function.
* The second observation is that we always move forward because, in the future, I’ll have the complete solution.
* To create the new node or determine the next step of the algorithm, I only need to calculate or process the current state.
* The `low` and `high` variables act as constraints.
* The `zero` and `one` variables represent the steps or jumps needed to reach the next feasible node.

With all this information, I can build the DP approach.
### DP approach
```cpp
class Solution {
public:
    const int MOD = 1e9 + 7;
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<long long> dp(high + max(one, zero) + 1, 0);
        for(int i=low; i<=high;i++){
            dp[i] = 1;
        }
        for(int sz=high;sz>=0;sz--){
            dp[sz] = dp[sz] % MOD + dp[sz+one] % MOD + dp[sz+zero] % MOD;
            dp[sz] %= MOD;
        }
        return dp[0];
    }
};
```
* What’s my base case? I only have an answer if `sz` is between `low` and `high` inclusive. So, i record that information in my `dp`.
* If you look at my implementation, it uses the same order of processing as the previous recursive solution. I need all the paths where `sz+one` and `sz+zero` have answer $>0$.
* Therefore, `dp[sz]` is defined as the number of ways I can build a valid string with size `sz`.

### Conclusion
* Finally, we can construct `dp` either from bottom-up or top-down. The main goal is to capture the patterns and relationships between the DP states.
* If you can create a recursive approach, you can transform it into an iterative approach by thinking in a DP manner.

### References
* Problem: https://leetcode.com/problems/count-ways-to-build-good-strings/?envType=daily-question&envId=2024-12-30