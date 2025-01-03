#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool debugme = false;

vector<string> p;

int HEIGHT, WIDTH;

static const int INF = INT_MAX;

static const int DOWN = 0;
static const int UP = 1;
static const int RIGHT = 2;
static const int LEFT = 3;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int getLeft(int d){
    if(d == 0) return 2;
    if(d == 1) return 3;
    if(d == 2) return 1;
    return 0;
}

int getRight(int d){
    if(d == 0) return 3;
    if(d == 1) return 2;
    if(d == 2) return 0;
    return 1;
}

//int getLeft(int d)  { return (d + 3) % 4; }
//int getRight(int d) { return (d + 1) % 4; }

vector<vector<vector<int>>> runDijkstra3D(
	int startY, int startX,
	int startDir
	){
    vector<vector<vector<int>>> dist(HEIGHT, vector<vector<int>>(WIDTH, vector<int>(4, INF)));   
    // min heap def
    typedef tuple<int, int, int, int> State;
    priority_queue<State, vector<State>, greater<State>> pq;
    // its end node
    if(startDir == -1){
	for(int d=0;d<4;d++){
	    dist[startY][startX][d] = 0;
	    pq.push({0, startY, startX, d});
	}
    }else{
	dist[startY][startX][startDir] = 0;
	pq.push({0, startY, startX, startDir});
    }
    while(!pq.empty()){
	auto [c, y, x, d] = pq.top();
	pq.pop();
	
	if(c > dist[y][x][d]){
	    continue;
	}

	// move forward
	int ny = y + dy[d];
	int nx = x + dx[d];
	    
	if(ny >= 0 && nx >= 0 && ny < HEIGHT && nx < WIDTH && p[ny][nx] != '#'){
	    int forwardCost = c + 1;
	    if(forwardCost < dist[ny][nx][d]){
		dist[ny][nx][d] = forwardCost;
		pq.push({forwardCost, ny, nx, d});
	    }
	}

	int ld = getLeft(d);
	int costTurnLeft = c + 1000;
	if(dist[y][x][ld] > costTurnLeft){
	    dist[y][x][ld] = costTurnLeft;
	    pq.push({costTurnLeft, y, x, ld});
	}

	int rd = getRight(d);
	int costTurnRight = c + 1000;
	if(dist[y][x][rd] > costTurnRight){
	    dist[y][x][rd] = costTurnRight;
	    pq.push({costTurnRight, y, x, rd});
	}
    }
    return dist;
}

void p3d(vector<vector<vector<int>>> & dist){
    for(int y=0;y<HEIGHT;y++){
	cout << "y = " << y << endl;
	for(int x=0;x<WIDTH;x++){
	    cout << "["<< y << "," << x <<"] = ";
	    if(p[y][x] == '#'){
		cout << "# ";
		continue;
	    }else{
		int d = dist[y][x][0];
		int u = dist[y][x][1];
		int r = dist[y][x][2];
		int l = dist[y][x][3];
		cout << "{"<<d<<","<<u<<","<<r<<","<<l<<"} "; 
	    }
	}
	cout << endl << "---------------------" << endl;
    }
    cout << endl;

}

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

    cout << "start = ["<<start.first << "," <<start.second<<"]" << endl;
    cout << "end = ["<<end.first << "," << end.second<<"]" << endl;

    auto distS = runDijkstra3D(start.first, start.second, 2);
    auto distE = runDijkstra3D(end.first, end.second, -1);
    
    int bestScore = INF;
    for(int d = 0; d < 4; d++){
	bestScore = min(bestScore, distS[end.first][end.second][d]);
    }

    cout << bestScore << endl;
    //cout<<"distS"<<endl;
    //p3d(distS);
    //cout<<"distE"<<endl;
    //p3d(distE);
    
    auto turnCost = [&](int d1, int d2){
	if(d1 == d2) return 0;
	int diff = (d2 - d1);
	if(diff < 0) diff += 4;
	if(diff == 2){
	    return 2001;
	}
	return 1001;
    };

    int cnt = 0;
    for(int y=0;y<HEIGHT;y++){
	for(int x=0;x<WIDTH;x++){
	    if(p[y][x] == '#') continue;
	    
	    bool isBest = false;
	    for(int d=0;d<4 && !isBest;d++){
		int costS = distS[y][x][d];
		if(costS == INF) continue;
		int k = 0;
		if(d == 0) k = 1;
		if(d == 1) k = 0;
		if(d == 2) k = 3;
		if(d == 3) k = 2;
		int costE = distE[y][x][k];
		if(costE == INF) continue;
		int tot = costS + costE;
		//tot += turnCost(d, k);
		if(tot == bestScore){
		    isBest = true;
		}
	    }

	    if(isBest){
		cnt++;
	    }
	}
    }
    cout << cnt << endl;
   
    return 0;
}

