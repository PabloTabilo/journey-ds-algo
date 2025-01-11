---
title: "Rabin - Karp algorithm"
weight: 1
---
# Rabin - Karp Algorithm
The Rabin-Karp algorithm solves problems involving pattern matching within a string, where the complexity largely depends on the hash function used. This algorithm utilizes **rolling hashing** for string searching.

But what is rolling hashing?

## Rolling Hashing
In simple terms, rolling hashing is a technique used to compute hash values efficiently for substrings of a string. It uses a sliding window approach, where the next window's hash is updated based on the previous window instead of being recomputed from scratch.

Often, a single polynomial hash function is used, such as:
$$
H(s) = (c_0 \cdot p^{m-1} + c_1 \cdot p^{m-2} + ... + c_{m-1}) \mod M
$$

Where:
* $m$ is the size of the substring.
* $c_i$ is the character at position $i$.
* $p$ is the base or radix number.
* $M$ is the modulus.

## Key idea for Rabin-Karp Double Hashing
The Rabin-Karp algorithm uses the rolling hash technique with a **double hashing** approach. For each substring, the hash is computed as:

$$
Hash(s) = ( H_1(s), H_2(s) )
$$
Both hash functions should meet the following criteria:
* The modulus values of the two hash functions must be different $mod_1 \ne mod_2$.
* The base or radix values $p$, must also differ $p_1 \ne p_2$.

### Example Problem
This is an `easy` problem of leetcode.
#### 28. Find the Index of the First Occurrence in a String

Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.

Example 1:
```
Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
```

Example 2:
```
Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
 ```
Constraints:
```
1 <= haystack.length, needle.length <= 10^4
haystack and needle consist of only lowercase English characters.
```

## Code
```cpp
typedef long long ll;
class Solution {
public:
    const ll MOD1 = 1e9 + 7;
    const ll RADIX1 = 26;
    const ll MOD2 = 1e9 + 33;
    const ll RADIX2 = 27;
    pair<ll,ll> hashMe(string & s, int m){
        ll factor1 = 1, factor2 = 1;
        pair<ll, ll> ans = {0, 0};
        for(int i=m-1;i>=0;i--){
            ans.first += ((s[i]-'a') * factor1) % MOD1;
            factor1 = (factor1 * RADIX1) % MOD1;
            ans.second += ((s[i]-'a') * factor2) % MOD2;
            factor2 = (factor2 * RADIX2) % MOD2;
        }
        ans.first %= MOD1;
        ans.second %= MOD2;
        return ans;
    }
    int strStr(string haystack, string needle) {
        int m = needle.length();
        int n = haystack.length();
        if(n < m) return -1;

        ll MAX_WEIGHT1 = 1, MAX_WEIGHT2 = 1;
        for(int i=0;i<m;i++){
            MAX_WEIGHT1 = (MAX_WEIGHT1 * RADIX1) % MOD1;
            MAX_WEIGHT2 = (MAX_WEIGHT2 * RADIX2) % MOD2;
        }
        pair<ll,ll> hashNeedle = hashMe(needle, m);
        pair<ll, ll> hashHay;
        for(int i=0;i <=(n-m);i++){
            if(i == 0){
                hashHay = hashMe(haystack, m);
            }else{
                hashHay.first = ((hashHay.first * RADIX1)%MOD1 - ((haystack[i-1]-'a')*MAX_WEIGHT1)%MOD1 + (haystack[i+m-1]-'a') + MOD1) % MOD1;
                hashHay.second = ((hashHay.second * RADIX2)%MOD2 - ((haystack[i-1]-'a')*MAX_WEIGHT2)%MOD2 + (haystack[i+m-1]-'a') + MOD2) % MOD2;
            }
            if(hashNeedle.first == hashHay.first && hashNeedle.second == hashHay.second){
                return i;
            }
        }
        return -1;
    }
};
```
### Analyzing the code
#### Constants
```cpp
const ll MOD1 = 1e9 + 7;
const ll RADIX1 = 26;
const ll MOD2 = 1e9 + 33;
const ll RADIX2 = 27;
```
* This variables are `constant` and type `long long`, that represent the modulus $mod_i$ and base $p_i$ to each hash function $H_i(s)$.
#### Hash Function
```cpp
pair<ll,ll> hashMe(string & s, int m){
    ll factor1 = 1, factor2 = 1;
    pair<ll, ll> ans = {0, 0};
    for(int i=m-1;i>=0;i--){
        ans.first += ((s[i]-'a') * factor1) % MOD1;
        factor1 = (factor1 * RADIX1) % MOD1;
        ans.second += ((s[i]-'a') * factor2) % MOD2;
        factor2 = (factor2 * RADIX2) % MOD2;
    }
    ans.first %= MOD1;
    ans.second %= MOD2;
    return ans;
}
```
* This function call `hashMe` gonna give us a pair of type `long long`.
* This function computes the hash values for a string `s` and returns a pair of hashes.
* So if you see, we declare two variables `factor` both gonna storage the `RADIX` or base value that multiply `m` times for each `hash`.
* The `pair<ll,ll> ans` is the answer of the first and second hash value.
#### Rolling Hashing construction
Within the loop:
```cpp
for(int i=m-1;i>=0;i--){
    ans.first += ((s[i]-'a') * factor1) % MOD1; // multiply with the char, the minus 'a' is for get the number from ascii value
    factor1 = (factor1 * RADIX1) % MOD1; // accumulate the RADIX
}
ans.first %= MOD1;
``` 
* The first thing is we gonna iterate the `string` in reverse with a size of `m` steps.
* So, the first value must be `s[m-1]-'a' * factor1`, where `factor1` is `1`.
    * The next, `s[m-2] * factor1`, where `factor1 = 26`.
    * The next iteration `s[m-3] * factor1` where `factor1 = 26 * 26`.
    * And so on.
In simple terms, we construct this: 
$$
H(s) = (c_0 \cdot p^{m-1} + c_1 \cdot p^{m-2} + ... + c_{m-1}) \mod M
$$

#### Preprocess purpose and Sliding Window approach
```cpp
ll MAX_WEIGHT1 = 1, MAX_WEIGHT2 = 1;
for(int i=0;i<m;i++){
    MAX_WEIGHT1 = (MAX_WEIGHT1 * RADIX1) % MOD1;
    MAX_WEIGHT2 = (MAX_WEIGHT2 * RADIX2) % MOD2;
}
```
* This is for precalculating the radix $high$ degree value used in the sliding window approach, where:
$$
H_i(s) = H_i(s) \cdot \text{RADIX} - c_{i-1} \cdot \text{RADIX-High-degree} + c_{i + m - 1}
$$
* We perform this operation in constant time. The same technique is described in the book Introduction to Algorithms by MIT (where the radix value is `10`):

![Alt text](/images/rabinKarpCite.PNG)
**Figure 1**: *Introduction to Algorithms*, MIT, p. 991.

* Finally, with the previous method, we perform $O(n - m)$ iterations, where $n$ is the size of thee `text` and $m$ is the size of the `pattern`.

#### Why introduce the modulus?
```cpp
hashHay.first = ((hashHay.first * RADIX1)%MOD1 - ((haystack[i-1]-'a')*MAX_WEIGHT1)%MOD1 + (haystack[i+m-1]-'a') + MOD1) % MOD1;
```
Because the `hash` value can become very large, for example, in this problem, the radix value is `26` and if the size of the pattern is `100`, the maximum radix or high-degree radix would be, following our example, $26^{100}$. For that reason, we need to modularize to avoid bounds problems.
However, introducing a modulus increases the chances of collisions, also known as `spurious hit`.
#### How can we solve the spurious hit problem?
We can use __double hashing__. This method significantly reduces the probability of collisions because a value would need to produce the same hash from both hash functions, which is highly unlikely.
```cpp
if(hashNeedle.first == hashHay.first && hashNeedle.second == hashHay.second){
    return i;
}
```


### References
* Problem: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
* Cormen, Thomas H., Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. Introduction to Algorithms. 3rd ed. Cambridge: MIT Press, 2009. Chapter 32, String Matching. Available at https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf
* https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
* https://www.youtube.com/watch?v=io9yJ-KelgE&ab_channel=AryanMittal