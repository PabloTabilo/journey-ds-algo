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

    pair<int, int> start;
    pair<int, int> end;
    for(int y=0;y<HEIGHT;y++){
	for(int x=0;x<WIDTH;x++){
	    if(p[y][x] == 'S'){
		start = {y, x};
	    }
	    if(p[y][x] == 'E'){
		end = {y, x};
	    }
	}
    }
    
    dist[y][x] = 0;
    priority_queue<pair<int, pair<int, int>> pq;
    pq.insert({0, {start.first, start.end}});
    

    return 0;
}

