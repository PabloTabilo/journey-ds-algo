/**
 * @author      : $USER ($USER@$HOSTNAME)
 * @file        : StringMatching
 * @created     : Wednesday Jan 08, 2025 17:21:27 Pacific SA Daylight Time
 */
#include <bits/stdc++.h>
#include "kmp.h"

using namespace std;

int main(){
    string s, p;
    cin >> s;
    cin >> p;

    cout << "s = " << s << ", p = " << p << endl;
    
    kmp myKmp(p, s);

    vector<int> lps = myKmp.getLps();

    cout << "lps: "; for(auto x : lps) cout << x << " "; cout << endl;

    return 0;
}

