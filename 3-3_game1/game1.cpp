/*
博弈问题，可以使用动态规划求解。 状态定义：用F[i][j]表示第一个玩家先取时，
在第i到第j的子序列中能拿到的最高分；用S[i][j]表示第i到第j的子序列中所有数字的和；
用num[i]表示第1到第n的序列中第i个数。
边界条件：F[i][i]=num[i]
状态转移方程： F[i][j]=max{num[i]+S[i+1][j]-F[i+1][j],num[j]+S[i][j-1]-F[i][j-1]}
结果 p1=F[1][n]; p2=S[1][n]-F[1][n];
解析： num[i]+S[i+1][j]-F[i+1][j]表示的是，p1拿第i到第j最左边的数，
然后轮到p2在第i+1到第j的序列中先取，会剩下S[i+1][j]-F[i+1][j]，这些归p1。
refer to byvoid;
Note both player 1 and player 2 want best reuslt;
*/
/*
ID: haolink1
PROG: game1
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 100;
int num[MAX];
int N = 0, ori = 0;
int dp[MAX][MAX];
ifstream fin("game1.in");
ofstream cout("game1.out");

int Sum(int a, int b){
    int sum = 0;
    for(int i = a; i <= b; i++){
        sum += num[i];
    }
    return sum;
}

inline int Max(int a, int b){
    return a >= b ? a : b;
}

int MemorizedDynamic(int a, int b){
   if(dp[a+1][b] == ori)
       dp[a+1][b] = MemorizedDynamic(a+1,b);
   if(dp[a][b-1] == ori)
       dp[a][b-1] = MemorizedDynamic(a,b-1);
   return Max(num[a]+Sum(a+1,b)-dp[a+1][b],num[b]+Sum(a,b-1)-dp[a][b-1]);
}

int main(){
    fin >> N;
    for(int i = 0; i < N; i++){
        fin >> num[i];
    }
    memset(dp,0xF,sizeof(dp));
    ori = dp[0][0];
    for(int i = 0; i < N; i++){
        dp[i][i] = num[i];
    }
    int ans = MemorizedDynamic(0,N-1);
    int ans2 = Sum(0,N-1)-ans;
    cout << ans << " " << ans2 << endl;
}
