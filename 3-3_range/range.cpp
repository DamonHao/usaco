/*
Main idea
这道题可以动态规划。二维的动态规划。
状态定义：G[i][j]为以(i,j)为左上角顶点的正方形的最大边长。
边界条件：G[i][j]为初始读入的矩阵。
状态转移方程： G[i][j]=min{ G[i+1][j] , G[i][j+1] , G[i+1][j+1] } + 1;
解析： G[i+1][j] , G[i][j+1] , G[i+1][j+1]分别为(i,j)向下、向右、向右下一格的状况。
在(n-1,n-1)当且仅当三者都为1的时候，正方形才能扩充。从最右下向上，依次扩充即可。
refer to byvoid;
Note Dynamic programming's way to count the number of squares for each size;
This is a way of collecting solution during DP;
*/

/*
Executing...
   Test 1: TEST OK [0.000 secs, 3748 KB]
   Test 2: TEST OK [0.000 secs, 3748 KB]
   Test 3: TEST OK [0.000 secs, 3748 KB]
   Test 4: TEST OK [0.000 secs, 3748 KB]
   Test 5: TEST OK [0.000 secs, 3748 KB]
   Test 6: TEST OK [0.011 secs, 3748 KB]
   Test 7: TEST OK [0.054 secs, 3748 KB]

All tests OK.
*/

/*
ID: haolink1
PROG: range
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 250;
int dp[MAX][MAX];
int ans[MAX+1];
int N = 0;
ifstream fin("range.in");
ofstream cout("range.out");
void Init(){
    fin >> N;
    string str;
    for(int i = 0; i < N; i++){
        fin >> str;
        for(int j = 0; j < N; j++){
            dp[i][j] = str[j] - 48;
        }
    }
}

int Min(int a,int b,int c){
    int min = a <= b ? a : b;
    min = min <= c ? min : c;
    return min;
}

void Dynamic(){
    for(int i = N - 2; i >= 0; i--){
        for(int j = N - 2; j >= 0; j--){
            if(dp[i][j])//Note dp[i][j] must first be 1;
                dp[i][j] = Min(dp[i+1][j],dp[i+1][j+1],dp[i][j+1]) + 1;
            if(dp[i][j] > 1){
                for(int k = 2; k <= dp[i][j]; k++){//count the size of square whose upleft point is(i,j);
                    ans[k]++;
                }
            }
        }
    }
}

void Print(){
    for(int i = 2; i <= N; i++){
        if(ans[i]){
            cout << i <<" "<< ans[i] << endl; 
        }
    }
}

int main(){
    Init(); 
    Dynamic();
    Print();
    return 0;
}
