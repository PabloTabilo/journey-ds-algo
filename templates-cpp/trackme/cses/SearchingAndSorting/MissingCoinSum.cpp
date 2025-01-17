#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i=0;i<n;i++){
	cin >> a[i];
    }
    sort(a.begin(), a.end());
    ll ans = 1;
    for(ll c : a){
	if(c <= ans){
	    ans += c;
	}else{
	    break;
	}
    }
    cout << ans << '\n';
    return 0;
}

