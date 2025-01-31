#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int n, q;
    cin >> n >> q;
    vector<ll> prefix(n);
    for(int i=0;i<n;i++){
	ll a;
	cin >> a;
	prefix[i] = ( (i-1) >= 0 ? prefix[i-1] : 0 ) + a;
    }


    while(q--){
	int a, b;
	cin >> a >> b;
	a--;
	b--;
	cout << prefix[b] - ( (a-1) >= 0 ? prefix[a-1] : 0 ) << endl;
    }
    return 0;
}

