#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> play(n);
    for(int i=0;i<n;i++){
	cin >> play[i];
    }
    set<int> onWindow;
    int ans = -1;
    int l = 0;
    int r  = l;
    for(;l<n && r < n;l++){

	for( ;r < n; r++){
	    if(onWindow.count(play[r]) > 0) break;
	    onWindow.insert(play[r]);
	}

	ans = max(ans, int(onWindow.size()) ) ;
	
	for(;l<r;l++){
	    onWindow.erase(play[l]);
	    if(r < n && play[l] == play[r]) break;
	}
    }

    cout << ans << '\n';


    return 0;
}

