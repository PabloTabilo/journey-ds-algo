#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> s;
    s.insert(-2);
    int cnt = 0;
    for(int i=0;i<n;i++){
	cin >> a[i];
	auto it = s.lower_bound(a[i]);
	it--;
	int prev = *it;
	int d = abs(a[i] - prev);
	if(d != 1){
	    cnt++;
	}else{
	    s.erase(it);
	}
	s.insert(a[i]);
    }
    cout << cnt << endl;
    
    // 10 17 14 -> 2

    // 4 2 1 5 3 6
    // 1 2 3 1 2 1
    //
    // 4 5
    // 2 3
    // 1 6
    //
    
    // 4 2 1 5 3
    // 1 2 3 1 3
    //
    // 4     5
    //     1   3
    //   2
    //
    //
    //i:0 
    //{4}
    //i:1
    //{4, 2}
    //i:2
    //{4, 2, 1}
    //i:3
    //{4, 5} are increasing
    //{5, 2, 1}
    //i:4

    return 0;
}

