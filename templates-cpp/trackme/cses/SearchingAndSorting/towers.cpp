#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<int> c(n);
    multiset<int> s;
    for(int i=0;i<n;i++){
	cin >> c[i];
	if(s.empty()){
	    s.insert(c[i]);
	    continue;
	}
	//cout << "c[i] = " << c[i] << endl;
	auto it = s.lower_bound(c[i]+1);
	if(it == s.end()){
	    it--;
	}
	auto x = *it;
	//cout << "x = " << x << endl;
	if(x <= c[i]){
	    s.insert(c[i]);
	}else if(x > c[i]){
	    s.erase(it);
	    s.insert(c[i]);
	}
    }
    cout << s.size() << endl;

    return 0;
}

