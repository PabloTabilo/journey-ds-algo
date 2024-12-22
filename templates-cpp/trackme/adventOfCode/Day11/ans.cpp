#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    string input_line;
    getline(cin, input_line);
    deque<ll> dq;
    istringstream iss(input_line);
    ll inum;
    while(iss >> inum){
	dq.push_back(inum);
    }
    int ope = 25; // part1
    //int ope = 75; // part2
    while(ope--){ 
	cout << "curr ope = " << ope << endl;
	cout << "curr dq.size() = " << int(dq.size()) << endl;
	deque<ll> f; // future
	while(dq.size()){
	    ll num = dq.front();
	    dq.pop_front();

	    if(num == 0){
		f.push_back(1);
		continue;
	    }
	    string snum = to_string(num);
	    int n = snum.length();
	    if( (n % 2) == 0){
		int mid = n / 2;
		string p1 = snum.substr(0, mid);
		string p2 = snum.substr(mid);
		ll p1ll = stoll(p1);
		ll p2ll = stoll(p2);
		f.push_back(p1ll);
		f.push_back(p2ll);
	    }else{
		f.push_back(num*2024);
	    }
	}
	dq = f;
    }
    cout << int(dq.size()) << endl;
    return 0;
}

