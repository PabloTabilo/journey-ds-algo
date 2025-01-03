#include <bits/stdc++.h>
#include <regex>
using namespace std;

using ll = long long;

ll a, b, c;

vector<pair<ll, ll> > instr;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string line;
    while(getline(cin, line)){
	if(line.empty()){
	    break;
	}
	sscanf(line.c_str(), "Register A: %lld", &a);
	sscanf(line.c_str(), "Register B: %lld", &b);
	sscanf(line.c_str(), "Register C: %lld", &c);
    }

    while(getline(cin, line)){
	if(line.empty()) break;
	regex reg("Program: ");
	line = regex_replace(line, reg, "");
	int n = line.length();
	int i = 0;
	while(i < n){
	    ll i1 = (ll) (line[i]-'0');
	    ll o1 = (ll) (line[i+2]-'0');
	    instr.push_back({i1, o1});
	    i += 4;
	}
    }

    cout << "a, b, c = " << a << "," << b << "," << c << endl;
    cout << "instr:"<<endl;
    for(auto x : instr){
	cout << "{"<<x.first<<","<<x.second<<"}"<<endl;
    }


    return 0;
}

