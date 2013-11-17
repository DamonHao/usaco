/*
ID: 
PROG:money
LANG:C++
*/
/*
方法2：
如果我们在模拟过程中稍微做一点变动就会发现一种效率更高的算法，如下：
在方法一的模拟过程中，对于每一步的描述可以表达如下“在第i张桌子上我应该拿取多少个硬币？”，现在改为“在第i张桌子上我是否应该再拿取一个硬币？（如果不拿，那就走向下一张桌子）”
此时思考的角度就从“拿多少个（选择数为O(n)）”到“拿与不拿（选择数为O(1)）”，可见选择数变少了，但是子问题发生了变化。
方法1的子问题可以表达如下“在前i-1张桌子上拿取总额为j-m*a[i]的方法数”，而方法2的子问题变为“当再拿取一个硬币时，在前i张桌子上拿取总额为j – a[i]的方法数”与“不再拿硬币时，在前i张桌子上拿取总额为j的方法数”，至于“最优子结构”问题读者自己证明。
因此可得如下动规方程：dp[i][j] = dp[i][j-a[i]] + dp[i-1][j]，dp[i][j-a[i]]是再拿一个的情况，dp[i-1][j]是不再拿走向下一张桌子的情况。 （提示：设在第i张桌子上拿取了m个硬币，当m>0时， 所有的方法都被dp[i][j-a[i]]包含了，因此当走向下一张桌子时仅需要考虑m=0的情况。）
可见子问题数没变而选择数减少了一个数量级，因此时间效率提高到O(v*n)
*/
#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("money.in");
//ofstream cout("money.out");
unsigned long long dp[25][10001];
int main(){
    int v,n,a[30];
    fin>>v>>n;
    int i,j;
    for(i=0;i!=v;++i)
        fin>>a[i];
    for(j=1;j<=n;++j)
        if(j%a[0]==0)
                dp[0][j]=1;
    for(i=0;i!=v;++i)
        dp[i][0]=1;
    for(i=1;i!=v;++i)
        for(j=1;j<=n;++j){
            if (j - a[i] >= 0){
                dp[i][j] = dp[i - 1][j] + dp[i][j - a[i]];
            }
            else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    cout<<dp[v-1][n]<<endl;
    return 0;
}
