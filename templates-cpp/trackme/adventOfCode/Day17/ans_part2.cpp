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
    /* REVERSE ENGINEERING APPROACH
     *
	Register A: 2024
	Register B: 0
	Register C: 0

	Program: 0,3,5,4,3,0
     * What's the lowest value must be A for get the output == input program?
     * answer = 117440
     * 0
     * 3, a = 0
     * Program : 0
     * 5, 4 -> a % 8 = 0
     * 0, 3 -> a = a / (1 << 3) = 0 -> a = 3 / 8 = 0
     *
     * Program : 3
     * 5, 4 -> a % 8 = 3 -> a = 3
     * 0, 3 -> a = a / (1<<3) = 3 -> 8 * 3 = a = 24 (28)
     *
     * Program : 4
     * 5, 4 -> a % 8 = 4 -> a = 24 + 4
     * 0, 3 -> a = 229 / 8 = 28 -> 28 * 8 = 224
     *
     * Program : 5
     * 5, 4 -> a % 8 = 229 % 8 = 5 -> 224 + 5 = 229
     * 0, 3 -> a = 1835 / 8 = 229 -> 229 * 8 = 1832
     *
     * Program : 3
     * 5, 4 -> a % 8 = 3 -> 1832 + 3
     * 0, 3 -> a = 14680 / 8 = 1835 -> 1835 * 8 = 14680
     *
     * Program : 0
     * 5, 4 -> a % 8 = 14680 % 8 = 0
     * 0, 3 -> a = a / 8 = 14680 -> 14680 * 8
     *
     * a = 117440
     * 
     *
     * Register A: 28422061
	Register B: 0
	Register C: 0

	Program: 2,4,1,1,7,5,1,5,4,2,5,5,0,3,3,0
     *
     * a = 0
     * (1) a = (a / 8) = 0 -> a in [1, 7]
     * Program: 0 >> b = 0 or multiply of 8
     * (2) b % 8 = 0
     * (3) b = (b ^ c) -> c = 0 or multiply 8
     * (4) b = (b ^ 5)
     * (5) c = (a / 2^b)
     * (6) b = (b ^ 1)
     * (7) b = a % 8
     *
     * a > 0
     * (1) a = (a / 8) > 0
     * Program: 3 >> b = 3 or multiply of 8 + 3
     * (2) b % 8 = 3
     * (3) b = (b ^ c)
     * (4) b = (b ^ 5)
     * (5) c = (a / 2^b)
     * (6) b = (b ^ 1)
     * (7) b = a % 8
     *
     * a > 0
     * (1) a = (a / 8) > 0
     * Program: 3 >> b = 3 or multiply of 8 + 3
     * (2) b % 8 = 3
     * (3) b = (b ^ c)
     * (4) b = (b ^ 5)
     * (5) c = (a / 2^b)
     * (6) b = (b ^ 1)
     * (7) b = a % 8
     *
     *
     * 3, 0 -> a = 0
     * 0, 3 -> a = a / 8 = 0
     * Program: 0
     * 5, 5 -> b % 8 = 0 -> b = 0
     * 4, 2 -> b = (b ^ c) = 0 -> ((b ^ 5) ^ c) % 8 = 0 
     * 1, 5 -> b = (b ^ 5) = 6
     * 7, 5 -> c = a / (1 << b) -> c = 1, a = 8, b = 3
     * 1, 1 -> b = (b ^ 1) = 0 -> b = 0
     * 2, 4 -> b = a % 8 = 0 (x: a is multiply of 8)
     *
     * 3, 0 -> a != 0 -> propose a = 8
     * 0, 3 -> a = a / 8 = ? -> a = 64
     * Program : 3
     * 5, 5 -> b % 8 = 0 -> b = 3
     * 4, 2 -> b = (b ^ c) = 3 -> b and c not share 3 as bit
     * 1, 5 -> b = (b ^ 5) = ?
     * 7, 5 -> c = a / (1 << b) -> c = 0, a = 0
     * 1, 1 -> b = (b ^ 1) = 0 -> b = 0
     * 2, 4 -> b = a % 8 = 0 (x: a is multiply of 8)
     *
     *
     *
     *
     * */
    
    auto combo = [](ll k){
	if(k <= 3) return k;
	if(k == 4) return a;
	if(k == 5) return b;
	if(k == 6) return c;
	throw std::invalid_argument("not possible Combo");
    };

    cout << "a, b, c = " << a << "," << b << "," << c << endl;
    cout << "instr: "; for(auto x : instr) cout << x << " "; cout << endl;
    // simulation
    ll LIMIT = 1e8 + 1;
    bool stop = false;
    for(ll ai=1;ai<LIMIT && !stop;ai++){
	a = ai;
	//cout << "start with a = " << a << endl;
	vector<ll> out;
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
	if(out.size() == instr.size()){
	    bool poss = true;
	    for(int i=0;i<out.size();i++){
		if(out[i] != instr[i]){
		    poss = false;
		    break;
		}
	    }
	    if(poss){
		cout << "A = " << ai << endl;
		stop = true;
	    }
	}
    }
    return 0;
}

