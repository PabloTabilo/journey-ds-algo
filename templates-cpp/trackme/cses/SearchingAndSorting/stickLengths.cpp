#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<ll> p(n);
    for(int i=0;i<n;i++){
	cin >> p[i];
    }
    
    // f(x) = sum |p_i - x| -> the median minimize this convex function
    // remember that it's a convex function so has a single global minimum
    //
    // Why binary search here doesn't work?
    // because bs assume a continuous and strictly
    // increasing or decreasing function
    sort(p.begin(), p.end());
    ll median1 = p[n/2];
    ll median2 = p[n/2 - 1];
    ll cost1 = 0, cost2 = 0;
    for(auto pi : p){
	cost2 += abs(median1 - pi);
	cost1 += abs(median2 - pi);
    }

    cout << min(cost1, cost2) << endl;
    return 0;
}

