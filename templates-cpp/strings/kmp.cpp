#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// pi = longest prefix of the suffix at position i
vector<int> kmp(string & s){
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
    }
    return pi_s;
}

int main(){
    // Simple problem:
    // Find the words that are substrings of the same set words, example:
    vector<string> words = {"mass", "as", "hero", "superhero"};
    // answer must be ["as", "hero"] because both are substrings of the set words, each are substring of "mass" and "superhero"
    auto comp = [](auto &l, auto &r){
            if(l.length() != r.length()){
                return l.length() < r.length();
            }
            return l < r;
        };
    // Why sort? for evit duplications
    sort(words.begin(), words.end(), comp);
    int n = words.size();
    string prev;
    vector<string> ans;
    for(int i=0;i<n;i++){
            string a = words[i];
            if(prev == a) continue; // duplicate
            for(int j=i+1;j<n;j++){
                string b = words[j];
                if(a.size() > b.size()) break; // its not necessary continue
                //cout << "a = " << a << ", b = " << b << endl;
                string t = a + '#' + b;
                int sz = a.length();
                vector<int> lps = kmp(t);
                //cout << "lps:"; for(auto x : lps) cout << x << " "; cout << endl;
                bool is_pattern = false;
                for(auto x : lps){
                    if(x >= sz){
                        ans.push_back(a);
                        is_pattern = true;
                        break;
                    }
                }
                if(is_pattern) break;
            }
            prev = a;
        }
    cout << "ans: { "; for(auto s : ans) cout << s << " "; cout << "}" << endl;
    return 0;
}
