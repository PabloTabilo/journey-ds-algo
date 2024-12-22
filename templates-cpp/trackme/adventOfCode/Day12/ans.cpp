#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<string> puzzle;
    {
	string t;
	while(true){
	    if(!getline(cin, t)) break;
	    puzzle.push_back(t);
	}
    }
    //cout << "puzzle:"<<endl;for(auto s : puzzle){for(auto c : s) cout << c << " ";cout << endl;}
    int n = puzzle.size();
    int m = puzzle[0].size();
    vector<vector<int>> c(n, vector<int>(m, -1));
    int dx[4] = {0,0,1,-1};
    int dy[4] = {-1,1,0,0};
    int compo = 1;
    ll ans = 0;
    for(int i=0;i<n;i++){
	for(int j=0;j<m;j++){
	    if(c[i][j] == -1){
		char mustBe = puzzle[i][j];
		//cout << "mustBe = " << mustBe << endl;
		queue<pair<int,int>> qpos;
		qpos.push({i, j});
		set<pair<int,int>> path;
		ll area = 0;
		ll per = 0;
		// mark
		while(!qpos.empty()){
		    auto [x, y] = qpos.front();
		    qpos.pop();
		    //cout << "x, y = " << x << "," << y << endl;
		    if(c[x][y] != -1) continue;
		    c[x][y] = compo;
		    path.insert({x,y});
		    area++;
		    for(int k=0;k<4;k++){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if(puzzle[nx][ny] != mustBe) continue;
			if(c[nx][ny] != -1) continue;
			qpos.push({nx, ny});
			//cout << "push >> " << nx << "," << ny << endl;
		    }
		}
		// area and perimeter
		for(auto [x, y] : path){
		    for(int k=0;k<4;k++){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m){
			    per++;
			}
			else if(puzzle[nx][ny] != mustBe){
			    per++;
			}
		    }
		}
		//cout << "area = "<< area << ", per = " << per << endl;
		ll res = area * per;
		//cout << "res = " << res << endl;
		ans += res;
		compo++;
	    }
	}
    }
    cout << ans << endl;
    return 0;
}

