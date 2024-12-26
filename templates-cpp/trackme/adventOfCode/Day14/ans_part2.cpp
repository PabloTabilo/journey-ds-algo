#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int X = 101;
int Y = 103;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<vector<int>> robots;
    {
	string line;
	vector<int> t(4);
	int x, y, vx, vy;
	while(getline(cin, line)){
	    if(line.empty()) continue;
	    sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &vx, &vy);
	    t[0] = x;
	    t[1] = y;
	    t[2] = vx;
	    t[3] = vy;
	    robots.push_back(t);
	}
    }
    set<vector<string>> seen;
    int mx = -1;
    int rep_max = -1;
    for(int rep = 1; rep<=100000; rep++){
	vector<string> puzzle(Y, string(X, ' '));
	for(int i=0;i<int(robots.size());i++){
	    int& x = robots[i][0];
	    int& y = robots[i][1];
	    int vx = robots[i][2];
	    int vy = robots[i][3];
	    x = (((x + vx) % X) + X) % X;
	    y = (((y + vy) % Y) + Y) % Y;
	    puzzle[y][x] = 'X';
	}
	//cycle found
	if(seen.find(puzzle) != seen.end()){
	    cout << "rep = " << rep << endl;
	    break;
	}
	seen.insert(puzzle);
	// This part is for see complete simulation
	//for(auto s : puzzle){
	//    printf("%s\n", s.c_str());
	//}
	//cout << endl;
	//cout << "rep = " << rep << endl;
	//cout << "------------------------------------------------------------------------" << endl;
    }
    return 0;
}

