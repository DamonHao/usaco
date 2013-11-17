/*
ID: haolink1
PROG: money
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int coins[25];
long long dp[25][10001];

//Main idea:
//Dynamic Programming
//dp[i][j] denote the number of ways to  construct money j by coins[0...i]
//state transition equation:
//dp[i][j] = dp[i-1][j] + dp[i-1][j-coins[i]] + ...dp[i-1][j-m*coins[i]]
//if j - m * coins[i] >= 0;
int main(){
    ifstream fin("money.in");
    int coins_num = 0;
    int N = 0;
    fin >> coins_num >> N;
    for(int i = 0; i < coins_num; i++){
        fin >> coins[i];
    }
    //Boundary condition  
    for(int i = 1; i <= N; i++){
        //Check whether money i can be constructed by coins[0]
        if((i % coins[0]) == 0)
            dp[0][i] = 1; 
    }
    //Note dp[0][0]
    //dp[i][0] count for dp[i+1][j - m*coins[i+1]], that is money j is 
    //constructed only by coins[i+1]. So the value of dp[i][0] is 1;
    for(int i = 0; i < coins_num; i++){
        dp[i][0] = 1;
    }
    for(int i = 1; i < coins_num; i++){
        for(int j = 1; j <= N; j++){
            dp[i][j] = dp[i-1][j];
            int ways = j / coins[i];
            for(int m = 1; m <= ways; m++){
                dp[i][j] += dp[i-1][j - m*coins[i]];
            }
        }
    }
    ofstream fout("money.out");
    fout << dp[coins_num-1][N] << endl;
    return 0;
}
