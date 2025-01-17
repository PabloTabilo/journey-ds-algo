#include <bits/stdc++.h>

using namespace std;

// https://www.hackerrank.com/challenges/extra-long-factorials/problem?isFullScreen=true

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */
// can occur problems with MLE if you use this, better O(1) Memory sol
//const int LIMI = 100;
//vector<string> dp(LIMI);

string sumeStr(string a, string b){
    int extra = 0;
    string t = "";
    while(a.size() > 0 && b.size() > 0){
        char lastA = a.back();
        char lastB = b.back();
        a.pop_back();
        b.pop_back();
        int x = lastA-'0';
        int y = lastB-'0';
        int z = x + y + extra;
        if( z < 10){
            t.push_back(char(z + '0'));
            extra = 0;
        }else{
            while(z >= 10){
                int d = z%10;
                t.push_back(char(d + '0'));
                z /= 10;
            }
            extra = z;
        }
    }
    
    while(a.size() > 0){
        char lastA = a.back();
        a.pop_back();
        int x = lastA-'0';
        int z = x + extra;
        if( z < 10){
            t.push_back(char(z + '0'));
            extra = 0;
        }else{
            while(z >= 10){
                int d = z%10;
                t.push_back(char(d + '0'));
                z /= 10;
            }
            extra = z;
        }
    }
    
    if(extra > 0){
        t.push_back(char(extra + '0'));
        extra = 0;
    }

    reverse(t.begin(), t.end());
    return t;
}

string createNum(int times, string base){
    string res = base;
    times--;
    while(times--){
        res = sumeStr(res, base);
    }
    return res;
}

//void initializeDp(){
    //dp[1] = "1";
    //for(int i=2;i<=LIMI;i++){
    //    dp[i] = createNum(i, dp[i-1]);
    //}
    //for(int i=1;i<=10;i++){cout << "dp["<<i<<"] = " << dp[i] << endl;}
//}

void extraLongFactorials(int n) {
    if(n == 1){
        cout << "1" << endl;
        return;
    }
    string prev = "1";
    string curr = "";
    for(int i=2;i<=n;i++){
        curr = createNum(i, prev);
        prev = curr;
    }
    cout << curr << endl;
    //cout << dp[n] << endl;
}

int main()
{
    // 1 <= n <= 100
    int n = 25;
    // output of factorial: 15511210043330985984000000
    extraLongFactorials(n);
    // input: 45
    // output: 119622220865480194561963161495657715064383733760000000000
    extraLongFactorials(45);

    return 0;
}
