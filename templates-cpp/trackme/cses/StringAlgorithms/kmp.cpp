/**
 * @author      : $USER ($USER@$HOSTNAME)
 * @file        : kmp
 * @created     : Wednesday Jan 08, 2025 17:51:10 Pacific SA Daylight Time
 */

#include "kmp.h"
// string t = pattern + "#" + string
kmp::kmp(std::string & pattern, std::string & a){
    t = pattern + "#" + a;
    n = t.length();
    lps.resize(n, 0);
    build();
}
void kmp::build(){
    for(int i=1;i<n;i++){
	int j = lps[i-1];
	while(j > 0 && t[i] != t[j]){
	    j = lps[j-1];
	}
	if(t[i] == t[j]){
	    j++;
	}
	lps[i] = j;
    }
}

std::vector<int> kmp::getLps(){
    return lps;
}
