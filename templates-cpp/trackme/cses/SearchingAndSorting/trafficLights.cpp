#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int x, n;
    cin >> x >> n;
    
    set<int> lights;
    unordered_map<int, pair<int, int>> upperAndLowerForLight;
    map<int, int> mx;
    lights.insert(0);
    lights.insert(x);
    int ans = -1; 
    for(int i=0; i < n; i++){
	int light;
	cin >> light;
	auto it_r = lights.lower_bound(light);
	auto it_l = lights.lower_bound(light-1);
	int rv = *it_r;
	int lv = *it_l;
	if(lv == rv){
	    it_l--;
	    lv = *it_l;
	}
	//cout << "light = " << light << endl;
	//cout << "lv = " << lv << ", rv = " << rv << endl;
	// is a trafic light? change boundaries;
	if(lv != 0){
	    //cout << "change rv of lv =" << lv << endl;
	    int ul_lv = upperAndLowerForLight[lv].second;
	    //cout << "ul_lv = " << ul_lv << endl;
	    int sz = ul_lv - lv;
	    //cout << "sz = " << sz << endl;
	    mx[sz]--;
	    if(mx[sz] == 0){
		mx.erase(sz);
	    }
	    upperAndLowerForLight[lv].second = light;
	    //cout << "ok lv" << endl;
	    mx[(light - lv)]++;
	}
	if(rv != x){
	    //cout << "change lv of rv =" << rv << endl;
	    int ll_rv = upperAndLowerForLight[rv].first;
	    //cout << "ll_rv = " << ll_rv << endl;
	    int sz = rv - ll_rv;
	    //cout << "sz = " << sz << endl;
	    mx[sz]--;
	    if(mx[sz] == 0){
		mx.erase(sz);
	    }
	    upperAndLowerForLight[rv].first = light;
	    //cout << "ok rv" << endl;
	    mx[(rv - light)]++;
	}
	//cout << "insert light - lv = " << (light - lv) << endl;	
	//cout << "insert rv - light = " << (rv - light) << endl;	
	
	mx[(light - lv)]++;
	mx[(rv - light)]++;
	
	ans = (*prev(mx.end())).first;

	cout << ans << " ";
	// cout << endl;
	//cout << "------------------------------------" << endl;

	upperAndLowerForLight[light] = {lv, rv};
	lights.insert(light);
    }

    // 1. max can be same sz for differents lights 
    // 2. if i add a new light, the lights around the boundaries
    // that's lower_bound on i+1 and i-1
    // must be affected her boundaries for this new i

    return 0;
}

