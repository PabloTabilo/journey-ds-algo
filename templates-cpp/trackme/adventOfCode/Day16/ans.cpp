#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<string> p;

int HEIGHT, WIDTH;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    {
	string line;
	while(getline(cin, line)){
	    if(line.empty()) break;
	    p.push_back(line);
	}
    }
    HEIGHT = p.size();
    WIDTH = p[0].size();
    
    vector<vector<int>> dist(HEIGHT, vector<int>(WIDTH, INT_MAX));
    vector<vector<char>> prev(HEIGHT, vector<char>(WIDTH, '.'));
    vector<vector<pair<int, int>>> prevPos(HEIGHT, vector<pair<int, int> >(WIDTH));

    pair<int, int> start;
    pair<int, int> end;
    queue<pair<int, int>> q;
    for(int y=0;y<HEIGHT;y++){
	for(int x=0;x<WIDTH;x++){
	    if(p[y][x] == 'S'){
		start = {y, x};
		prev[y][x] = 'S';
		prevPos[y][x] = {y, x};
		dist[y][x] = 0;
		q.push({y, x});
	    }
	    if(p[y][x] == 'E'){
		end = {y, x};
		prev[y][x] = 'E';
		prevPos[y][x] = {y, x};
	    }
	}
    }
    

    int dy[4] = {1, -1, 0, 0};
    int dx[4] = {0, 0, 1, -1};

    auto dirChar = [&](int k){
	if(k == 0) return 'v';
	if(k == 1) return '^';
	if(k == 2) return '>';
	return '<';
    };
    
    cout << "init puzzle" << endl;
    for(auto y : p){
	for(auto x: y){
	    cout << x << " ";
	}
	cout << endl;
    }
    while(!q.empty()){
	auto [y, x] = q.front();
	q.pop();
	if(p[y][x] == 'E'){
	    continue;
	}
	for(int k=0;k<4;k++){
	    int ny = y + dy[k];
	    int nx = x + dx[k];
	    
	    if(ny < 0 || nx < 0 || ny >= HEIGHT || nx >= WIDTH) continue;
	    if(p[ny][nx] == '#') continue;
	    
	    int w = prev[y][x] == dirChar(k) ? 1 : 1001;
	    if(p[y][x] == 'S'){
		w = 1;
	    }
	    if(dist[ny][nx] > dist[y][x] + w){
		if(p[ny][nx] != 'E') p[ny][nx] = dirChar(k);
		dist[ny][nx] = dist[y][x] + w;
		prev[ny][nx] = dirChar(k);
		prevPos[ny][nx] = {y, x};
		q.push({ny, nx});
	    }
	}
    }
    
    cout << "final puzzle" << endl;
    for(auto y : p){
	for(auto x: y){
	    cout << x << " ";
	}
	cout << endl;
    }
    
    cout << "cost matrix" << endl;
    for(auto y : dist){
	for(auto x: y){
	    if(x == INT_MAX) cout << "INF" << " ";
	    else cout << x << " ";
	}
	cout << endl;
    }

    cout << dist[end.first][end.second] << endl;
    vector<pair<int, int> > path;
    int y = end.first;
    int x = end.second;
    pair<int, int> pai;
    while( !(y == start.first && x == start.second) ){
	path.push_back({y, x});
	pai = prevPos[y][x];
	y = pai.first;
	x = pai.second;
    }
    path.push_back({y, x});
    
    for(auto [yy, xx] : path){
	cout << "{"<<yy<<","<<xx<<"} = " << p[yy][xx] << endl;
    }

    return 0;
}

