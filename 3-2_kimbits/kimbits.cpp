/*
动态规划。尝试暴搜，但是超时了

分析：
设长度为n的01串，1的个数不大于v的个数为dp[n,v]
方程：dp[n,v]=dp[n-1,v]+dp[n-1,v-1]; //分别表示在当前位加上0和加上1时的两种状况
边界：dp[i,0]=dp[0,j]=1;
这样我们得到了所有的dp[n,v],需要做的就是据此构造出所求字符串.
设所求串为S,假设S的位中最高位的1在自右向左第K+1位，那么必然满足dp[K,L]< i,dp[K+1,L] >=i,
这样的K是唯一的。所以S的第一个1在从右至左第K+1位.因为有F[K,L]个串第K+1位上为0，
所以所求的第i个数的后K位就应该是满足"位数为K且串中1不超过L-1个"这个条件的第i-F[K,L]个数。  
--参考 jzzlee 
*/
/*
ID: haolink1
PROG: kimbits
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
int dp[32][32];

int Dynamic(int i, int j){
    if(dp[i][j] != 0)
        return dp[i][j];
    else{
        dp[i][j] = Dynamic(i-1,j)+Dynamic(i-1,j-1);
        return dp[i][j];
    }
}

int main(){
    int N = 0,L = 0;
    //Note: I maybe the 2147483648th element, so I's data type should be unsigned int or long long;
    long long I = 0;
    ifstream fin("kimbits.in");
    ofstream cout("kimbits.out");
    fin >> N >> L >> I;
    for(int i = 0; i <= N; i++){
        dp[i][0] = 1;
    }
    for(int j = 1; j <= L; j++){
        dp[0][j] = 1;
    }
    for(int k = N-1; k >= 0; k--){
        if(Dynamic(k,L) < I){
            cout << 1;
            I -= Dynamic(k,L);
            L--;
        }else{
            cout << 0;
        }
    }
    cout << endl;
    return 0;
}
