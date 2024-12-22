#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    string input_line;
    getline(cin, input_line);
    map<ll, ll> curr;
    istringstream iss(input_line);
    ll inum;
    while(iss >> inum){
	curr[inum]++;
    }
    int ope = 75;
    while(ope--){ 
	map<ll, ll> fu; // future
	for(auto [k, v] : curr){
	    if(k == 0){
		fu[1]+=v;
		continue;
	    }
	    string snum = to_string(k);
	    int n = snum.length();
	    if( (n % 2) == 0){
		int mid = n / 2;
		string p1 = snum.substr(0, mid);
		string p2 = snum.substr(mid);
		fu[stoll(p1)]+=v;
		fu[stoll(p2)]+=v;
	    }else{
		fu[k * (ll) 2024]+=v;
	    }
	}
	curr = fu;
    }
    ll ans = 0;
    for(auto [k, v] : curr){
	ans += v;
    }
    cout << ans << endl;
    return 0;
}

