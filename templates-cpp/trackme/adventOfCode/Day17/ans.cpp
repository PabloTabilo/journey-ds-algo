#include <bits/stdc++.h>
#include <regex>
using namespace std;

using ll = long long;

ll a = 0, b = 0, c = 0;

vector<ll> instr;

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
	cout << "line = " << line << endl;
	int n = line.length();
	int i = 0;
	while(i < n){
	    ll i1 = (ll) (line[i]-'0');
	    ll o1 = (ll) (line[i+2]-'0');
	    instr.push_back(i1);
	    instr.push_back(o1);
	    i += 4;
	}
    }

    cout << "a, b, c = " << a << "," << b << "," << c << endl;
    cout << "instr: "; for(auto x : instr) cout << x << " "; cout << endl;
    auto combo = [](ll k){
	if(k <= 3) return k;
	if(k == 4) return a;
	if(k == 5) return b;
	if(k == 6) return c;
	throw std::invalid_argument("not possible Combo");
    };
    vector<ll> out;
    int j = 0;
    ll ip = 0;
    int n = instr.size();
    while(ip < n){
	ll i = instr[ip];
	ip++;
	ll o = instr[ip];
	ip++;
	if(i == 0){
	    //cout << "i = " << i << endl;
	    //cout << "o = " << o << endl;
	    //cout << "combo(o) = " << combo(o) << endl;
	    a /= (1<<combo(o));
	    //cout << "a = " << a << endl;
	}
	if(i == 1){
	    b = (b ^ o);
	}
	if(i == 2){
	    //cout << "o  = " << o << endl;
	    //cout << "combo(o) = " << combo(o) << endl;
	    b = combo(o) % 8;
	}
	if(i == 3){
	    if(a == 0) continue;
	    // now the instruction pointer
	    // and the operand are the same
	    else ip = o;
	}
	if(i == 4){
	    b = (b ^ c);
	}
	if(i == 5){
	    //cout << "i = " << i << endl;
	    //cout << "o = " << o << endl;
	    //cout << "combo(o) = " << combo(o) << endl;
	    out.push_back(combo(o)%8);
	    //cout << "combo(o)%8 = " << combo(o)%8 << endl;
	}
	if(i == 6){
	    b = a / (1<<combo(o));
	}
	if(i == 7){
	    c = a / (1<<combo(o));
	}
    }
    //cout << "register post operations: a, b, c = " << a << "," << b << "," << c << endl;
    for(int i=0;i<out.size();i++){
	auto x = out[i];
	if(i < (out.size()-1)) cout << x << ",";
	else cout << x;
    }
    cout << endl;
    return 0;
}

