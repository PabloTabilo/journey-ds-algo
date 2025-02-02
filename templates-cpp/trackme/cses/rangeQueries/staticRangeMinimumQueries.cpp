#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;
    int h = log2(n);
    vector<vector<int>> st(h+1, vector<int>(n,INT_MAX));
    for(int i=0;i<n;i++){
	cin >> st[0][i];
    }

    for(int k = 1; k <= h; k++){
	for(int i=0;i<n;i++){
	    if( (i + (1<<k) - 1) < n){
		st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))]);
	    }
	}
    }
/*
    cout << "st:" << endl;
    for(auto y : st){
	for(auto x : y) cout << x << " ";
	cout << endl;
    }
    cout << endl;
*/
    while(q--){
	int l, r;
	cin >> l >> r;
	l--; r--;
	int sz = r - l + 1;
	int j = l;
	int ans = INT_MAX;
	for(int k = h; j < n && k >= 0 && sz > 0; k--){
	    if((1<<k) > sz) continue;
	    //cout << "sz = " << sz << endl;
	    //cout << "k, j = " << k << ", " << j << endl;
	    ans = min(ans, st[k][j]);
	    //cout << "st[k][j] = " << st[k][j] << endl;
	    //cout << "ans = " << ans << endl;
	    sz -= (1 << k);
	    j += (1 << k);
	}
	cout << ans << endl;
    }

    return 0;
}

