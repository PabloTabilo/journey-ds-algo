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

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);

    {
        string line;
        bool nxt = false;
        while (getline(cin, line)) {
            if (line.empty()) {
                break;
            }
            string line2;
            for (char c : line) {
                if (c == '#') {
                    line2.push_back('#');
                    line2.push_back('#');
                }
                if (c == '.') {
                    line2.push_back('.');
                    line2.push_back('.');
                }
                if (c == '@') {
                    line2.push_back('@');
                    line2.push_back('.');
                }
                if (c == 'O') {
                    line2.push_back('[');
                    line2.push_back(']');
                }
            }
            p.push_back(line2);
        }
        while (getline(cin, line)) {
            if (line.empty()) {
                break;
            }
            if (moves.size() == 0) {
                moves = line;
            } else {
                moves.append(line);
            }
        }
    }
    
    bool debugMe = false;

    HEIGHT = p.size();
    WIDTH  = p[0].size();

    int row = -1;
    int col = -1;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (p[y][x] == '@') {
                row = y;
                col = x;
                break;
            }
        }
    }

    auto get_dir = [](char c) {
        if (c == '^') return make_pair(-1, 0);
        if (c == 'v') return make_pair(1, 0);
        if (c == '<') return make_pair(0, -1);
        return make_pair(0, 1);
    };

    auto isBox = [](int y, int x) {
        return p[y][x] == ']' || p[y][x] == '[';
    };

    if(debugMe){
    cout << "p:" << endl;
    for (auto &rowstr : p) {
        for (auto x : rowstr) cout << x << " ";
        cout << endl;
    }
    cout << "moves : " << moves << endl;

    }

    for (char m : moves) {
        if(debugMe) cout << "--------------------------------" << endl;
        if(debugMe) cout << "moves = " << m << endl;
        auto [dr, dc] = get_dir(m);
        if(debugMe) cout << "dr, dc = " << dr << "," << dc << endl;
        if(debugMe) cout << "@ row = " << row << ", col = " << col << endl;
        int r = row + dr;
        int c = col + dc;
        if(debugMe) cout << "new visit : p[r][c] = p[" << r << "][" << c << "] = " << p[r][c] << endl;

        if (p[r][c] == '.') {
            p[row][col] = '.';
            p[r][c]      = '@';
            row          = r;
            col          = c;
        } 
        else if (p[r][c] == '#') {
            r = row;
            c = col;
            continue;
        } 
        else {
            // push left or right
            if (dc != 0) {
                int r2 = r;
                int c2 = c;
                bool isPoss = false;
                do {
                    if (p[r2][c2] == '.') {
                        // moves
                        isPoss = true;
                        break;
                    }
                    if (p[r2][c2] == '#') {
                        // not moves
                        isPoss = false;
                        break;
                    }
                    r2 += dr;
                    c2 += (dc + dc);
                } while (true);

                if (isPoss) {
                    p[row][col] = '.';
                    p[r][c]     = '@';
                    if (dc == 1)  p[r2][c2] = ']';
                    if (dc == -1) p[r2][c2] = '[';
                    for (int k = c + dc; k != c2; k += dc) {
                        if (p[r2][k] == ']') {
                            p[r2][k] = '[';
                        } else if (p[r2][k] == '[') {
                            p[r2][k] = ']';
                        }
                    }
                    row = r;
                    col = c;
                } else {
                    r = row;
                    c = col;
                }
            } 
            // push up or down
            else {
                int r2 = r;
                int c2 = c;
                bool isPoss = true;
                char stored = p[r2][c2];

                queue<pair<int, int>> q;
                q.push({r2, c2});
                map<pair<int, int>, char> boxes;

                while (!q.empty()) {
                    auto [yy, xx] = q.front();
                    q.pop();
                    if (boxes.find({yy, xx}) != boxes.end()) {
                        continue;
                    }
                    boxes[{yy, xx}] = p[yy][xx];
                    if (p[yy][xx] == ']') {
                        q.push({yy, xx - 1});
                    } else {
                        q.push({yy, xx + 1});
                    }
                    if (isBox(yy + dr, xx)) {
                        q.push({yy + dr, xx});
                    }
                }
		if(debugMe){
                cout << endl << "boxes : ";
                for (auto &[k, v] : boxes) {
                    cout << "{" << k.first << "," << k.second << "} = " << v << "  ";
                }
                cout << endl;

		}

                for (auto &[k, v] : boxes) {
		    if(debugMe) cout << "p["<<k.first<<"]["<<k.second<<"] = "<< p[k.first+dr][k.second] << endl;
                    if (p[k.first + dr][k.second] == '#') {
                        isPoss = false;
                        break;
                    }
                }
                if(debugMe) cout << "isPoss = " << isPoss << endl;
                if(debugMe) cout << "r2, c2 = " << r2 << ", " << c2 << endl;

                if (isPoss) {
                    for (auto &[k, v] : boxes) {
                        p[k.first][k.second] = '.';
                    }
                    for (auto &[k, v] : boxes) {
                        p[k.first + dr][k.second] = v;
                    }
                    
		    p[row][col] = '.';
                    p[r][c]     = '@';
                    if (stored == '[') {
                        p[r][c + 1] = '.';
                    } else {
                        p[r][c - 1] = '.';
                    }

                    row = r;
                    col = c;
                } else {
                    r = row;
                    c = col;
                }
            }
        }
	
	if(debugMe){
        cout << "p:" << endl;
        for (auto &rowstr : p) {
            for (auto x : rowstr) cout << x << " ";
            cout << endl;
        }

	}
    }
    if(debugMe){
    cout << "final p:" << endl;
    for (auto &rowstr : p) {
        for (auto x : rowstr) cout << x << " ";
        cout << endl;
    }

    }

    
    ll score = 0;
    for (ll y = 0; y < HEIGHT; y++){
        for (ll x = 0; x < WIDTH; x++){
            if (p[y][x] == '['){
                score += (100LL*y + x);
            }
        }
    }
    cout << score << endl;
    
    return 0;
}

