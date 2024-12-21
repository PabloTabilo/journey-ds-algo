#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string disk;
    cin >> disk;
    string trans;
    
    ll idx = 0;
    //cout <<"disk = " << disk << endl;
    for(int i=0;i<disk.size();i+=2){
	int use = disk[i] - '0';
	int free = (i+1) < disk.size() ? disk[i+1] - '0' : 0;
	string idxStr = to_string(idx);
	idx++;
	while(use--){
	    trans.append("|");
	    trans.append(idxStr);
	    trans.append("|");
	} 
	while(free--) trans.push_back('.');
    }
    //cout << "trans = " << trans << endl;
    
    int n = trans.size();
    int l = 0;
    int r = n-1;
    vector<ll> ans;
    while(l < r){
	//cout << "l, r = " << l << ", " << r << endl;
	while(l < r && trans[l] == '|'){
	    l++;
	    deque<char> dq;
	    while(trans[l] != '|'){
		dq.push_front(trans[l]);
		l++;
	    }
	    l++;
	    string outStr(dq.begin(), dq.end());
	    //cout << "while l = " << l << ", outStr = " << outStr << endl;
	    ll v = stoll(outStr);
	    ans.push_back(v);
	}
	
	while(l < r && trans[l] != '.'){
	    l++;
	} 

	while(l < r && trans[r] == '.') r--;
	
	while(l < r && trans[r] == '|'){
	    r--;
	    deque<char> dq;
	    while(trans[r] != '|'){
		dq.push_front(trans[r]);
		r--;
	    }
	    r--;
	    string outStr(dq.begin(), dq.end());
	    //cout << "while r = " << r << ", outStr = " << outStr << endl;
	    ll v = stoll(outStr);
	    ans.push_back(v);
	    break;
	}
	l++;
    }
    
    //cout << "ans: "<< endl;for(auto x : ans) cout << x << " "; cout << endl;
    ll sz = ans.size();
    ll res = 0;
    for(ll i=0;i<sz;i++){
	res += (ans[i]*i);
    }
    cout << res << endl;
    
    return 0;
}

