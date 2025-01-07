---
title: "Knuth-Morris-Pratt"
weight: 1
---
# KMP

## Code
```cpp
class Solution {
public:
    bool kmp_substr(string & s, int sz){
        int n = s.length();
        vector<int> pi_s(n, 0);
        for(int i=1;i < n;i++){
            int j = pi_s[i-1];
            while(j > 0 && s[i] != s[j]){
                j = pi_s[j-1];
            }
            if(s[i] == s[j]){
                j++;
            }
            pi_s[i] = j; 
            if(j >= sz){
                return true;
            }
        }
        return false;
    }
    vector<string> stringMatching(vector<string>& words) {
        auto comp = [](auto &l, auto &r){
            if(l.length() != r.length()){
                return l.length() < r.length();
            }
            return l < r;
        };
        sort(words.begin(), words.end(), comp);
        //cout << "words:"; for(auto x : words) cout << x << " "; cout << endl;
        int cnt = 0;
        int n = words.size();
        vector<string> ans;
        string prev;
        for(int i=0;i<n;i++){
            string a = words[i];
            if(prev == a) continue;
            for(int j=i+1;j<n;j++){
                string b = words[j];
                if(a.length() > b.length()) break;
                string t = a + '#' + b;
                if(kmp_substr(t, a.length())){
                    ans.push_back(a);
                    break;
                }
            }
            prev = a;
        }
        return ans;
    }
};
```
### Interesting Articles
* https://cp-algorithms.com/string/prefix-function.html
* https://usaco.guide/adv/string-search?lang=cpp

### References
* Problem: https://leetcode.com/problems/string-matching-in-an-array/?envType=daily-question&envId=2025-01-07