#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int X = 101;
int Y = 103;

int x, y, vx, vy;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<vector<int>> robots;
    {
	string line;
	vector<int> t(4);
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
    auto quad = [](int x, int y){
	//cout << "x, y = " << x << "," << y << endl;
	//cout << "X, Y = " << X << ", " << Y << endl;
	//cout << "(X/2), (Y/2) = " << (X/2) << "," << (Y/2) << endl;
	if(x >= 0 && x <(X/2) && y>=0 && y < (Y/2)){
	    return 1;
	}
	if(x > (X/2) && x < X && y >= 0 && y < (Y/2)){
	    return 2;
	}
	if(x >= 0 && x<(X/2) && y > (Y/2) && y < Y){
	    return 3;
	}
	if(x > (X/2) && x < X && y > (Y/2) && y < Y){
	    return 4;
	}
	return -1;
    };
    
    int times = 100;
    unordered_map<int, ll> cnt = {{1,0},{2,0},{3,0},{4,0},{-1,0}};
    for(int i=0;i<int(robots.size());i++){
	x = robots[i][0];
	y = robots[i][1];
	vx = robots[i][2];
	vy = robots[i][3];
	int nx = ((x + vx * times) % X + X) % X;
	int ny = ((y + vy * times) % Y + Y) % Y;
	int q = quad(nx, ny);
	cnt[q]++;
    }
    ll safetyFactor = cnt[1]*cnt[2]*cnt[3]*cnt[4];
    cout << safetyFactor << endl;
    return 0;
}

