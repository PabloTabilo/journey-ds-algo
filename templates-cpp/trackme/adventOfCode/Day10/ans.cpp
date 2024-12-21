#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<vector<int>> puzzle;
    vector<pair<int, int>> starts;
    int n;
    int m;
    {
	string line;
	while(true){
	    if(!getline(cin, line)) break;
	    vector<int> t;
	    m = line.length();
	    for(int i=0;i<m;i++){
		char c = line[i];
		t.push_back(c-'0');
		if((c-'0') == 0){
		    starts.push_back({int(puzzle.size()),i});
		}
	    }
	    puzzle.push_back(t);
	}
    }
    //cout << "puzzle:" << endl; for(auto x : puzzle){for(auto y : x) cout << y << " "; cout << endl;}
    n = puzzle.size();
    //cout << "n, m = " << n << "," << m << endl;
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    int ans = 0;
    for(auto [i, j] : starts){
	//cout << "i, j = " << i << "," << j << endl;
	queue<int> qslope;
	queue<pair<int, int>> qpos;
	qslope.push(0);
	qpos.push({i,j});
	int cnt = 0;
	vector<vector<bool>> vis(n, vector<bool>(m, false));
	while(!qpos.empty()){
	    auto [x, y] = qpos.front();
	    int curr_slope = qslope.front();
	    qpos.pop();
	    qslope.pop();
	    //cout << "x, y = " << x << "," << y << endl;
	    //cout << "curr_slope = " << curr_slope << endl;
	    if(vis[x][y]) continue;
	    vis[x][y] = true;
	    if(curr_slope == 9){
		cnt++;
		continue;
	    }
	    for(int k=0;k<4;k++){
		int nx = x + dx[k];
		int ny = y + dy[k];
		if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
		if(vis[nx][ny]) continue;
		int nslope = puzzle[nx][ny];
		if(nslope != curr_slope + 1) continue;
		qpos.push({nx, ny});
		qslope.push(nslope);
	    }
	}
	ans += cnt;
    }
    cout << ans << endl;
    return 0;
}

