#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int ans = 0;

vector<vector<int>> puzzle;
vector<vector<int>> diffWays;

int n;
int m;

int dfs(int x, int y){
    int curr_slope = puzzle[x][y];
    if(curr_slope == 9){
	return 1;
    }
    int ways = 0;
    for(int k=0;k<4;k++){
	int nx = x + dx[k];
	int ny = y + dy[k];
	if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
	int nslope = puzzle[nx][ny];
	if(nslope != curr_slope + 1) continue;
	ways += dfs(nx, ny);
    }
    return ways;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<pair<int, int>> starts;
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
    for(auto [i, j] : starts){
	ans += dfs(i, j);
    }
    cout << ans << endl;
    return 0;
}

