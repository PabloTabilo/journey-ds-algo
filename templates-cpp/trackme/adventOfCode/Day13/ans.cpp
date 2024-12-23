#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll cA = 3;
ll cB = 1;

ll xA, yA, xB, yB, xP, yP;

int maxTimes = 100;

const ll LIMIT = 1e9 + 1;

vector<vector<ll>> dp;

ll f(int i, int j, int times){
    if(times > maxTimes) return LIMIT;
    if(i < 0 || j < 0 || i >= int(dp.size()) || j >= int(dp[0].size())) return LIMIT;
    if(i == xP && j == yP){
	return 0;
    }
    if(dp[i][j] != LIMIT){
	return dp[i][j];
    }

    dp[i][j] = min(dp[i][j], cA + f(i+xA, j+yA, times+1));
    dp[i][j] = min(dp[i][j], cB + f(i+xB, j+yB, times+1));
    return dp[i][j];
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<pair<ll, ll> > movesA;
    vector<pair<ll, ll> > movesB;
    vector<pair<ll, ll> > prizes;

    {
	string line;
	while(getline(cin, line)){
	    if(line.empty()) continue;

	    if(line.find("Button A:") != string::npos){
		sscanf(line.c_str(), "Button A: X+%lld, Y+%lld", &xA, &yA);
		movesA.push_back({xA, yA});

		getline(cin, line);
		sscanf(line.c_str(), "Button B: X+%lld, Y+%lld", &xB, &yB);
		movesB.push_back({xB, yB});

		getline(cin, line);
		sscanf(line.c_str(), "Prize: X=%lld, Y=%lld", &xP, &yP);
		prizes.push_back({xP, yP});
	    }
	}
    }
    int n = movesA.size();
    ll ans = 0;
    for(int k = 0; k<n;k++){
	xA = movesA[k].first; 
	yA = movesA[k].second;
	xB = movesB[k].first; 
	yB = movesB[k].second;
	xP = prizes[k].first; 
	yP = prizes[k].second;

	ll addMe = 10000000000000LL;

	xP += addMe;
	yP += addMe;
	
	// i*xA + j*xB = xP (1)
	// i*yA + j*yB = yP (2)
	//
	// i = (xP - j*xB) / xA (1.1)
	// (1.1) -> xA*(2)
	// (xP - j*xB)*yA + j*yB*xA = yP*xA
	// xP*yA - j * xB * yA + j * yB * xA = yP * xA
	// j * (yB*xA - yA*xB) = (yP*xA - xP*yA)
	// j * (A x B) = (P x A)
	ll j = (yP*xA - xP*yA) / (yB*xA - yA*xB);
	ll i = (yP*xB - xP*yB) / (-yB*xA + yA*xB);
	//cout << "i = " << i << ", j = " << j << endl;
	ll tot_cost = LLONG_MAX;
	if((i*xA + j*xB) == xP){
	    if((i*yA + j*yB) == yP){
		//assert(i <= 100 && j <= 100);
		tot_cost = min(tot_cost, 3*i + j);
	    }
	}
	if(tot_cost == LLONG_MAX) tot_cost = 0;
	ans += tot_cost;
    }
    cout << "ans = " << ans << endl;
    return 0;
}

