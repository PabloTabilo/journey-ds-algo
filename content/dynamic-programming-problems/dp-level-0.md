---
title: "DP Level 0"
weight: 1
---
# DP Level 0
Dynamic Programming (DP) problems generally involve the optimization of some discrete problem. This means that the solution typically revolves around breaking the problem into smaller subproblems, solving each of them, and combining the results to find the best possible answer.

The objective of this problem is to find the **minimum cost** while adhering to the given rules for valid passes.

## 983. Minimum Cost For Tickets
* Level `medium`.

### Problem statement
You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array `days`. Each day is an integer from `1` to `365`.

Train tickets are sold in __three different ways__:

* a 1-day pass is sold for `costs[0]` dollars,
* a 7-day pass is sold for `costs[1]` dollars, and
* a 30-day pass is sold for `costs[2]` dollars.

The passes allow that many days of consecutive travel.

* For example, if we get a 7-day pass on day `2`, then we can travel for `7` days: `2`, `3`, `4`, `5`, `6`, `7`, and `8`.

Return the _minimum number of dollars you need_ to travel every day in the given list of days.

 
#### Example 1:
```
Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
```
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
* On day 1, you bought a 1-day pass for `costs[0] = $2`, which covered day 1.
* On day 3, you bought a 7-day pass for `costs[1] = $7`, which covered days 3, 4, ..., 9.
* On day 20, you bought a 1-day pass for `costs[0] = $2`, which covered day 20.

In total, you spent $11 and covered all the days of your travel.`

#### Example 2:
```
Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
```
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
* On day 1, you bought a 30-day pass for `costs[2] = $15` which covered days 1, 2, ..., 30.
* On day 31, you bought a 1-day pass for `costs[0] = $2` which covered day 31.

In total, you spent $17 and covered all the days of your travel.
 

#### Constraints:

* 1 <= `days.length` <= 365
* 1 <= `days[i]` <= 365
* `costs.length` == 3
* 1 <= `costs[i]` <= 1000

### First Thoughts
* The first thing to consider is how to iterate over the `vector<int> days`. It must be sorted because we need to process some days before others.
* The second thing is that the problem gives us options. We have four choices: take a 1-day pass, a 7-day pass, a 30-day pass, or skip the current day if it’s not in the `vector<int> days`.
* The third thing is that we need to minimize a cost function using the information stored in `vector<int> costs`.
* With these characteristics, I can implement a solution using a recursive approach.

Here’s the code:
```cpp
class Solution {
public:
    vector<bool> mustBuy;
    int n;
    int f(int d, vector<int>& days, vector<int>& costs){
        if(d > days[n-1]) return 0;
        if(!mustBuy[d]){
            return f(d+1, days, costs);
        }
        int best = INT_MAX;
        int op1 = costs[0] + f(d+1, days, costs);
        int op2 = costs[1] + f(d+7, days, costs);
        int op3 = costs[2] + f(d+30, days, costs);
        best = min(best, op1);
        best = min(best, op2);
        best = min(best, op3);
        return best;    
    }
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        mustBuy.resize(366,false);
        sort(days.begin(), days.end());
        this->n = days.size();
        for(int d : days) mustBuy[d] = true;
        return f(days[0], days, costs);
    }
};
```

* Why use `vector<bool> mustBuy`? It’s a boolean vector that keeps track of whether a specific day needs to be processed or not.
* The code works, but the time complexity is terrible, around $O(3^n)$, where $n$ can be as large as 365.
* The first thing to notice is the **structure** of the problem/solution is consistent—it’s the **same** for each **subproblem**. To solve the problem for day `d`, I need to check if it’s a valid day in `vector<int> days` and calculate the three cost options.
* The second observation is that we always move forward because, in the future, I’ll have the complete solution.
* The base case exists in the future. For this reason: `if(d > days[n-1]) return 0;`

With all this information, I can build the DP approach.

### DP approach
```cpp
class Solution {
public:
    vector<bool> mustBuy;
    int n;
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        mustBuy.resize(366,false);
        sort(days.begin(), days.end());
        this->n = days.size();
        for(int d : days) mustBuy[d] = true;
        vector<int> dp(days[n-1]+31,INT_MAX);
        for(int base=days[n-1]+1; base< (days[n-1]+31); base++) dp[base] = 0;
        
        for(int d=days[n-1];d>=0;d--){
            if(!mustBuy[d]){
                dp[d] = dp[d+1];
            }else{
                dp[d] = min(dp[d], costs[0]+dp[d+1]);
                dp[d] = min(dp[d], costs[1]+dp[d+7]);
                dp[d] = min(dp[d], costs[2]+dp[d+30]);
            }
        }
        return dp[0];
    }
};
```
* What’s my base case? I know that after the last day available, the contribution to my cost function is 0. So, all days beyond the last day must have a cost of 0.
```cpp
for(int base=days[n-1]+1; base< (days[n-1]+31); base++) dp[base] = 0;
```
* In this case, what's my `dp[d]`? It's defined as the minimum cost from day `d` to the last day available `day[n-1]`.
$$
dp[d] =
\begin{cases} 
dp[d+1], & \text{if } \texttt{!mustBuy[d]} \\\\ 
\min \left (
\begin{matrix}
dp[d], \\\\
\texttt{costs}_0 + dp[d+1], \\\\
\texttt{costs}_1 + dp[d+7], \\\\
\texttt{costs}_2 + dp[d+30]
\end{matrix}
\right), & \text{otherwise}
\end{cases}
$$

### Conclusion
* Finally, we can construct `dp` either from bottom-up or top-down. The main goal is to capture the patterns and relationships between the DP states.
* If you can create a recursive approach, you can transform it into an iterative approach by thinking in a DP manner.

### References
* Problem: https://leetcode.com/problems/minimum-cost-for-tickets/description/?envType=daily-question&envId=2024-12-31