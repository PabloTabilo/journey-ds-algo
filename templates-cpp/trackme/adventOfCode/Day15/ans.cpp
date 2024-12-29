#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<string> p;
string moves;
map<pair<int,int>, vector<bool>> blockWalls;

int WIDTH;
int HEIGHT;
// down, up, right, left
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    {
	string line;
	bool nxt = false;
	while(getline(cin, line)){
	    if(line.empty()){
		break;
	    }
	    p.push_back(line);
	}
	while(getline(cin, line)){
	    if(line.empty()){
		break;
	    }
	    if(moves.size() == 0){
		moves = line;
	    }else{
		moves.append(line);
	    }
	}
    }
    HEIGHT = p.size();
    WIDTH = p[0].size();
    int row = -1;
    int col = -1;
    for(int y=0;y<HEIGHT;y++){
	for(int x=0;x<WIDTH;x++){
	    if(p[y][x] == '@'){
		row = y;
		col = x;
		break;
	    }
	}
    }
    auto get_dir = [](char c){
	if(c == '^') return make_pair(-1,0);
	if(c == 'v') return make_pair(1,0);
	if(c == '<') return make_pair(0,-1);
	return make_pair(0,1);
    };

    //cout << "p:"<<endl; for(auto y : p){for(auto x : y) cout << x << " "; cout << endl;}
    //cout << "moves : " << moves << endl;
    for(char m : moves){
	//cout << "--------------------------------" << endl;
	//cout << "moves = " << m << endl;
	auto [dr, dc] = get_dir(m);
	//cout << "dr, dc = " << dr << "," << dc << endl;
	//cout << "@ row = " << row << ", col = " << col << endl;
	int r = row + dr;
	int c = col + dc;
	//cout << "new visit : p[r][c] = p["<<r<<"]["<<c<<"] = "<<p[r][c] << endl;
	if(p[r][c] == '.'){
	    p[row][col] = '.';
	    p[r][c] = '@';
	    row = r;
	    col = c;
	}
	if(p[r][c] == '#'){
	    r = row;
	    c = col;
	    continue;
	}
	if(p[r][c] == 'O'){
	    int r2 = r;
	    int c2 = c;
	    bool isPoss = false;
	    do{
		//cout << "onWhile : p[r2][c2] = p["<<r2<<"]["<<c2<<"] = "<<p[r2][c2] << endl;
		if(p[r2][c2] == '.'){
		    // moves
		    isPoss = true;
		    break;
		}
		if(p[r2][c2] == '#'){
		    // not moves
		    isPoss = false;
		    break;
		}
		r2 += dr;
		c2 += dc;
	    }while(true);
	    //cout << "isPoss = " << isPoss << endl;
	    if(isPoss){
		p[row][col] = '.';
		p[r][c] = '@';
		p[r2][c2] = 'O';
		row = r;
		col = c;
	    }else{
		r = row;
		c = col;
	    }
	}
	//cout << "p:"<<endl;for(auto y : p){for(auto x : y) cout << x << " "; cout << endl;}
    }
    //cout << "p:"<<endl;for(auto y : p){for(auto x : y) cout << x << " "; cout << endl;}
    ll score = 0;
    for(ll y=0;y<HEIGHT;y++){
	for(ll x=0;x<WIDTH;x++){
	    if(p[y][x] == 'O'){
		score += (100LL*y + x);
	    }
	}
    }
    cout << score << endl;
    return 0;
}

