/*
ID:jzzlee1
PROG:money
LANG:C++
*/
/*
 方法3：
注意到方法2中的动规方程：dp[i][j] = dp[i][j-a[i]] + dp[i-1][j]
我们在求dp[i][*]时仅会用到dp[i-1][*]，而不会用到dp[i-2][*],dp[i-3][*]等等。
这就表示，任何时刻我们都可以仅用两个数组来保存dp的值，而不用v个，公式就可以简化为： dp_2[j] = dp_2[j-a[i]] + dp_1[j]。
且在求dp_2[j]时，dp_2[j]的值可以是任意值而不会影响到dp_2[j]的正确性（因为它的值是由dp_2[j-a[i]]与dp_1[j]决定的），那么我们就可以用dp_2[j]的来保存dp_1[j]的值，公式可以改为： dp_2[j] = dp_2[j-a[i]] + dp_2[j]。
注意，当计算dp_2[j] = dp_2[j-a[i]] + dp_2[j]时，等号左边的dp_2[j]表示“前i张桌子拿取j元的方案数”，而等号右边的dp_2[j]表示“前i-1张桌子拿取j元的方案数”。
这就只需要用一个大小为O(n)的dp数组了。空间效率从O(v*n)提高到了O(n)。
*/
//#include<iostream>
#include<fstream>
#include<iostream>
using namespace std;
ifstream fin("money.in");
//ofstream fout("money.out");
unsigned long long dp[10001];
int main(){
    int v,n,a[30];
    fin>>v>>n;
    int i,j;
    for(i=0;i!=v;++i)
        fin>>a[i];
    for(j=0;j<=n;++j)
        if(j%a[0]==0)
            dp[j]=1;
    for(i=1;i!=v;++i)
        for(j=1;j<=n;++j){
            if (j - a[i] >= 0){
                dp[j] = dp[j] + dp[j - a[i]];
            }
        }
    cout<<dp[n]<<endl;
    return 0;
}
