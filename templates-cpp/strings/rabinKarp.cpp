#include<bits/stdc++.h>
#include <iostream>

using namespace std;
typedef long long ll;
class Solution {
public:
    const ll MOD1 = 1e9 + 7; // must be prime
    const ll RADIX1 = 26; // String with lowecase letters so range [0, 25] -> 26 radix
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