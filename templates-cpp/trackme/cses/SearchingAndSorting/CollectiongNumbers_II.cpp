
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int getSum(int * bit, int idx){
    idx = idx + 1;
    int sume = 0;
    while(idx > 0){
	sume += bit[idx];
	idx -= (idx & -idx);
    }
    return sume;
}

void updateBIT(int * bit, int idx, int n, int v){
    idx = idx + 1;
    while(idx <= n){
	bit[idx] += v;
	idx += (idx & -idx); // last bit
    }
    //cout << "update bit: "; for(int i=1;i<=n;i++){cout << bit[i] << " ";} cout << endl;
}

int * buildBITree(vector<int> a, int n){
    int * bit = new int[n+1];
    for(int i=0;i<=n;i++){
	bit[i] = 0;
    }
    for(int i=0;i<n;i++){
	updateBIT(bit, i, n, a[i]);
    }
    //cout << "bit: ";for(int i=1;i<=n;i++){cout << bit[i] << " ";}cout << endl;
    return bit;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> pos(n+1);
    vector<int> inv(n+1, 0);
    for(int i=0;i<n;i++){
	cin >> a[i];
	pos[a[i]] = i;
    } 
    int cnt = 1;
    for(int i=1;i<n;i++){
	if(pos[i] > pos[i+1]){
	    cnt++;
	    inv[i] = 1;
	}
    }

    int * bit = buildBITree(inv, n+1);
        
    //cout << "a: "; for(auto x : a) cout << x << " "; cout << endl;
    //cout << "pos: "; for(auto x : pos) cout << x << " "; cout << endl;
    //cout << "inv: "; for(auto x : inv) cout << x << " "; cout << endl;
    //cout << "getSum() = " << getSum(bit, n) << endl; 
    int i, j;
    while(m--){
	cin >> i >> j;
	i--;
	j--;

	int vi = a[i];
	int vj = a[j];

	swap(a[i], a[j]);
	
	pos[vi] = j;
	pos[vj] = i;

	int nxti = vi + 1;
	int previ = vi - 1;
	if(nxti <= n){
	    if(pos[vi] > pos[nxti] && !inv[vi]){
		inv[vi] = 1;
		updateBIT(bit, vi, n+1, 1);
	    }
	    else if(pos[vi] < pos[nxti] && inv[vi]){
		inv[vi] = 0;
		updateBIT(bit, vi, n+1, -1);
	    }
	}
	if(previ >= 1){
	    if(pos[previ] > pos[vi] && !inv[previ]){
		inv[previ] = 1;
		updateBIT(bit, previ, n+1, 1);
	    }
	    else if(pos[previ] < pos[vi] && inv[previ]){
		inv[previ] = 0;
		updateBIT(bit, previ, n+1, -1);
	    }
	}

	int nxtj = vj + 1;
	int prevj = vj - 1;
	if(nxtj <= n){
	    if(pos[vj] > pos[nxtj] && !inv[vj]){
		inv[vj] = 1;
		updateBIT(bit, vj, n+1, 1);
	    }
	    else if(pos[vj] < pos[nxtj] && inv[vj]){
		inv[vj] = 0;
		updateBIT(bit, vj, n+1, -1);
	    }
	}
	if(prevj >= 1){
	    if(pos[prevj] > pos[vj] && !inv[prevj]){
		inv[prevj] = 1;
		updateBIT(bit, prevj, n+1, 1);
	    }
	    else if(pos[prevj] < pos[vj] && inv[prevj]){
		inv[prevj] = 0;
		updateBIT(bit, prevj, n+1, -1);
	    }
	}

	//cout << "a: "; for(auto x : a) cout << x << " "; cout << endl;
	//cout << "pos: "; for(auto x : pos) cout << x << " "; cout << endl;
	//cout << "inv: "; for(auto x : inv) cout << x << " "; cout << endl;
	//cout << "getSum() = "; 
	cout << getSum(bit, n) + 1 << endl; 
    }
    
    // 10 17 14 -> 2

    // 4 2 1 5 3 6
    // 1 2 3 1 2 1
    //
    // 4 5
    // 2 3
    // 1 6
    //
    
    // 4 2 1 5 3
    // 1 2 3 1 3
    //
    // 4     5
    //     1   3
    //   2
    //
    //
    //i:0 
    //{4}
    //i:1
    //{4, 2}
    //i:2
    //{4, 2, 1}
    //i:3
    //{4, 5} are increasing
    //{5, 2, 1}
    //i:4

    return 0;
}

