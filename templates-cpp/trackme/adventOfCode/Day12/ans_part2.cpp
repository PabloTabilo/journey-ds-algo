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
		//cout << "calculate perimeter" << endl;
		//cout << "mustBe = " << mustBe << endl;
		ll corners = 0;
		// area and perimeter
		// the number of sides = number of corners
		for(auto [x, y] : path){
		    //cout << "x, y = " << x << "," << y << endl;
		    bool top = false;
		    bool bottom = false;
		    bool left = false;
		    bool right = false;
		    // corners
		    // top-left corner
		    //   *
		    // * A
		    // top-right corner
		    // * 
		    // A *
		    if((x-1)<0){
			top = true;
		    }
		    if((x-1)>= 0 && puzzle[x-1][y] != mustBe){
			top = true;
		    }
		    if((y-1)<0){
			left = true;
		    }
		    if((y-1)>=0 && puzzle[x][y-1] != mustBe){
			left = true;
		    }
		    if(top && left){
			//cout << "is a top-left corner" << endl;
			corners++;
		    }
		    if((y+1)>=m){
			right = true;
		    }
		    if((y+1)<m && puzzle[x][y+1] != mustBe){
			right = true;
		    }
		    if(top && right){
			//cout << "is a top-right corner" << endl;
			corners++;
		    }
		    // bottom-left corner
		    // * A
		    //   *
		    // bottom-right corner
		    // A *
		    // * 
		    if((x+1)>=n){
			bottom = true;
		    }
		    if((x+1)<n && puzzle[x+1][y] != mustBe){
			bottom = true;
		    }
		    if(bottom && left){
			//cout << "is a bottom-left corner" << endl;
			corners++;
		    }
		    if(bottom && right){
			//cout << "is a bottom-right corner" << endl;
			corners++;
		    }
		    // special
		    // A *
		    // A A
		    if(!top && !right){
			if((x-1)>=0 && (y+1)<m && puzzle[x-1][y+1] != mustBe){
			    //cout << "is a diagonal top-right case" << endl;
			    corners++;
			}
		    }
		    if(!top && !left){
			if((x-1)>=0 && (y-1)>=0 && puzzle[x-1][y-1] != mustBe){
			    //cout << "is a diagonal top-left case" << endl;
			    corners++;
			}
		    }
		    if(!bottom && !right){
			if((x+1)<n && (y+1)<m && puzzle[x+1][y+1] != mustBe){
			    //cout << "is a diagonal bottom-right case" << endl;
			    corners++;
			}
		    }
		    if(!bottom && !left){
			if((x+1)<n && (y-1)>=0 && puzzle[x+1][y-1] != mustBe){
			    //cout << "is a diagonal bottom-left case" << endl;
			    corners++;
			}
		    }
		    //cout << "-----------------" << endl;
		}
		//cout << "area = "<< area << ", corners = " << corners << endl;
		ll res = area * corners;
		//cout << "res = " << res << endl;
		ans += res;
		compo++;
		//cout << "*************************" << endl;
	    }
	}
    }
    cout << ans << endl;
    return 0;
}

