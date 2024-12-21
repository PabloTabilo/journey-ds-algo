#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string disk;
    cin >> disk;
    string trans;
    
    ll idx = 0;
    //cout <<"disk = " << disk << endl;
    map<ll, int> use;
    set<pair< ll, pair<int, int>>  > free; 
    for(int i=0; i < disk.size();i+=2){
	int u = disk[i] - '0';
	int f = (i+1) < disk.size() ? disk[i+1] -'0' : 0;
	use[idx] = u;
	free.insert({idx, {0, f}});
	idx++;
    }

    //cout << "original use and free: " << endl;
    //cout << "use: "; for(auto [k, v] : use) cout << "{"<<k<<","<<v<<"} "; cout << endl;
    //cout << "free: "; for(auto [k, v] : free) cout << "{"<<k<<","<<"["<<v.first<<","<<v.second<<"]"<<"} "; cout << endl;
    //cout << ".............................." << endl;

    vector<ll> ans; // is sorted
    idx = 0;
    for(int i=0; i < disk.size();i+=2){
	while(use[idx] > 0){
	    ans.push_back(idx);
	    use[idx]--;
	}
	use.erase(idx);
	
	//cout << "idx = " << idx << " must be erase." << endl;
	
	if(use.size() == 0) break;
	// need to find last
	//cout << "use: "; for(auto [k, v] : use) cout << "{"<<k<<","<<v<<"} "; cout << endl;
	//cout << "free: "; for(auto [k, v] : free) cout << "{"<<k<<","<<"["<<v.first<<","<<v.second<<"]"<<"} "; cout << endl;
	
	auto use_tail = prev(use.end());
	auto free_head = free.begin();
	
	//cout << "free_head = {" << free_head->first << "," << "["<<free_head->second.first<<"," << free_head->second.second<<"]" << "}" << endl;
	
	// if spaces was release because we move a files
	while(free_head->second.first == -1){
	    for(int k=0;k < (free_head->second.second); k++){
		ans.push_back(0);
	    }
	    free.erase(free_head);
	    free_head = free.begin();
	    //cout << "free_head = {" << free_head->first << "," << "["<<free_head->second.first<<"," << free_head->second.second<<"]" << "}" << endl;
	}
	bool found = true;
	//cout << "prev while loop ans: "; for(auto x : ans) cout << x << " "; cout << endl;
	while(true){
	    //cout << "search candidate for free_head = {" << free_head->first << "," << "["<<free_head->second.first<<"," << free_head->second.second<<"]" << "}" << endl;
	    //cout << "candidate >> use_tail = {" << use_tail->first << "," << use_tail->second << "}" << endl;
	    if(use_tail->second < free_head->second.second){
		//free_head->second.second -= use_tail->second; // occupied memory
		free.insert({free_head->first, {0, (free_head->second.second - use_tail->second) }});
		free.erase(free_head);
		free_head = free.begin();

		free.insert({use_tail->first, {-1, use_tail->second}}); // new null spaces that are not available
		//free[use_tail->first] += use_tail->second; // new null spaces
		
		// when you move whole files
		// you generate null spaces
		//while(free[use_tail->first] > 0){
		//    pass_once.push_back(0);
		//    free[use_tail->first]--;
		//}
		//free.erase(use_tail->first);
		
		// Drop the files that you move to head
		// because never gonna use again
		
		while(use_tail->second){
		    ans.push_back(use_tail->first);
		    use_tail->second--;
		}
		use.erase(use_tail);
		use_tail = prev(use.end());
	    }else if(use_tail->second == free_head->second.second){
		//free[use_tail->first] += use_tail->second; // new null spaces
		free.insert({use_tail->first, {-1, use_tail->second}}); // new null spaces that are not available
		// when you move whole files
		// you generate null spaces
		//while(free[use_tail->first] > 0){
		//    pass_once.push_back(0);
		//    free[use_tail->first]--;
		//}
		// Drop the files that you move to head
		// because never gonna use again
		while(use_tail->second){
		    ans.push_back(use_tail->first);
		    use_tail->second--;
		}
		use.erase(use_tail);
		// all null spaces are empty
		free.erase(free_head);
		// is factible continue to the next idx
		break;
	    }
	    // the current chunk files are more than
	    // the space available, but you need to pass one time 
	    // over it
	    else{
		if(use_tail == use.begin()){
		    // not found a good candidate for fill the null spaces.
		    found = false;
		    break;
		}
		use_tail = prev(use_tail);
	    }
	    //cout << "while loop use: "; for(auto [k, v] : use) cout << "{"<<k<<","<<v<<"} "; cout << endl;
	    //cout << "while loop free: "; for(auto [k, v] : free) cout << "{"<<k<<","<<v<<"} "; cout << endl;
	}
	
	if(!found){
	    for(int k=0;k < (free_head->second.second); k++){
		ans.push_back(0);
	    }
	    free.erase(free_head);
	}

	idx++;
	//cout << "FINISH while loop use: "; for(auto [k, v] : use) cout << "{"<<k<<","<<v<<"} "; cout << endl;
	//cout << "FINISH while loop free: "; for(auto [k, v] : free) cout << "{"<<k<<","<<"["<<v.first<<","<<v.second<<"]"<<"} "; cout << endl;
	//cout << "post while loop ans: "; for(auto x : ans) cout << x << " "; cout << endl;
	//cout << "---------------" << endl;
    }

    //cout << "final ans: "; for(auto x : ans) cout << x << " "; cout << endl;
    //cout << "pass_once: "; for(auto x : pass_once) cout << x << " "; cout << endl;

    ll sz = ans.size();
    ll res = 0;
    for(ll i=0;i<sz;i++){
	res += (ans[i]*i);
    }
    cout << res << endl;
    
    return 0;
}

