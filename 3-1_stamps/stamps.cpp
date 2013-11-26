/*
Main idea:
This is a good Dynamic programming problem;
dp[i]=min{dp[i-value[j]]}+1 // (j=1..n and i-value[j]>=0)  
dp[i] means that to make up postage i,we need dp[i] stamps at least;
So, we increase i, and when dp[i] > K, the answer we want is i-1;
Note this problem request the number of contiguous postage values starting at 1 cent;
It request "contiguous postage",but we convert it to dynamic programming,which is good
at max/min subproblem or the sum of subproblem;
*/
/*
ID: haolink1
PROG: stamps
LANG: C++
*/

//#include <iostream>
#include <fstream>
using namespace std;
//Note here is 0x7FFFFFFE, not 0x7FFFFFFF, because we may
//request min to add 1;
const int INF = 0x7FFFFFFE;
int dp[2000001];
int value[50];

inline int Min(int a, int b){
    return a < b? a : b; 
}
//time complexity O(N*K*M)//M is max value among N stamps;
int main(){
    int K = 0, N = 0;
    ifstream fin("stamps.in");
    ofstream cout("stamps.out");
    fin >> K >> N;
    for(int i = 0; i < N; i++){
        fin >> value[i];
    }
    int postage = 0; int p_min = 0;
    dp[0] = 0; 
    while(dp[postage] <= K){
        postage++; p_min = INF;
        for(int i = 0; i < N; i++)
            if(postage >= value[i])
                p_min = Min(p_min,dp[postage - value[i]]);
        dp[postage] = p_min+1; 
    }
    cout << postage-1 << endl;
    return 0;
}
