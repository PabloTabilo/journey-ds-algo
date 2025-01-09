#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

struct kmp{
    std::vector<int> lps; //pi_s
    std::string t;
    int n;
    kmp(std::string & pattern, std::string & a);
    void build();
    std::vector<int> getLps(); // pi_s
};

kmp::kmp(std::string & pattern, std::string & a){
    t = pattern + "#" + a;
    n = t.length();
    lps.resize(n, 0);
    build();
}
void kmp::build(){
    for(int i=1;i<n;i++){
	int j = lps[i-1];
	while(j > 0 && t[i] != t[j]){
	    j = lps[j-1];
	}
	if(t[i] == t[j]){
	    j++;
	}
	lps[i] = j;
    }
}

std::vector<int> kmp::getLps(){
    return lps;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    string s, p;
    cin >> s;
    cin >> p;

    //cout << "s = " << s << ", p = " << p << endl;
    
    kmp myKmp(p, s);

    vector<int> lps = myKmp.getLps();

    //cout << "lps: "; for(auto x : lps) cout << x << " "; cout << endl;

    int m = p.length();
    int cnt = 0;
    for(auto x : lps){
	if(x == m){
	    cnt++;
	}
    }
    
    cout << cnt << endl;

    return 0;
}

