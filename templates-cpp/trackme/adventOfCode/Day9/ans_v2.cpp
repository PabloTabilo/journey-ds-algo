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
    map<ll, int> f;
    for(int i=0; i < disk.size();i+=2){
	int use = disk[i] - '0';
	int free = (i+1) < disk.size() ? disk[i+1] -'0' : 0;
	f[idx] = use;
	idx++;
    }

    //cout << "f: "; for(auto [k, v] : f) cout << "{"<<k<<","<<v<<"} "; cout << endl;
    
    vector<ll> ans;
    idx = 0;
    for(int i=0; i < disk.size();i+=2){
	//int use = disk[i];
	if(f.size() == 0) break;
	while(f[idx] > 0){
	    ans.push_back(idx);
	    f[idx]--;
	}
	f.erase(idx);
	//cout << "idx = " << idx << " must be erase." << endl;
	//cout << "post idx erase f: "; for(auto [k, v] : f) cout << "{"<<k<<","<<v<<"} "; cout << endl;
	idx++;
	int free = (i+1) < disk.size() ? disk[i+1] - '0' : 0;
	while(free > 0){
	    if(f.size() == 0) break;
	    auto last = prev(f.end());
	    //cout << "free = " << free << endl;
	    //cout << "last->first, last->second = " << last->first << "," << last->second << endl;
	    if(last->second <= free){
		free -= last->second;
		while(last->second){
		    ans.push_back(last->first);
		    last->second--;
		}
		f.erase(last);
	    }else{
		last->second -= free;
		while(free--){
		    ans.push_back(last->first);
		}
	    }
	}
	//cout << "post free >> f: "; for(auto [k, v] : f) cout << "{"<<k<<","<<v<<"} "; cout << endl;
	//cout << "---------------" << endl;
    }
    
    //cout << "ans: "; for(auto x : ans) cout << x << " "; cout << endl;

    ll sz = ans.size();
    ll res = 0;
    for(ll i=0;i<sz;i++){
	res += (ans[i]*i);
    }
    cout << res << endl;
    
    return 0;
}

