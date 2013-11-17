/*
ID: haolink1
PROG: nocows
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int dp[200][100];

//Main idea: 
//Dynamic Programming
//dp[i][j] denote the number of binary trees whose node number is i and height is less or equal to j;
//state transition equation:
//dp[i][j] = dp[m][j-1]*dp[i-1-m][j-1];
//dp[m][j-1] denote the left subtree with m nodes and no more than j-1 height ;
//and dp[i-1-m][j-1] denote the right subtree i-1-m nodes(the root take 1 node and left subtree take m),
//no more than j-1 height;
//So the number of birnary trees with i nodes and j height is dp[i][j]-dp[i][j-1];
//
int main(){
    ifstream fin("nocows.in");
    int node_num, hight;
    fin >> node_num >> hight;
    //boundary conditions
    for(int j = 1; j <= hight; j++){
        dp[1][j] = 1;
    }
    for(int i = 2; i <= node_num; i++){
        for(int j = 2; j <= hight; j++){
            for(int m = 1; m <= i-2; m++){
                //mod dp[i][j] by 9901 in case it exceed the int max positive value  and become negative;
                dp[i][j] = (dp[i][j] + dp[m][j-1]*dp[i-1-m][j-1])%9901;
            }
        }
    }
    ofstream fout("nocows.out");
    //Note: after mod operation, dp[node_num][hight] may be less than dp[node_num][hight-1];
    //So we add 9901 at the end;
    fout << (dp[node_num][hight] - dp[node_num][hight-1] + 9901)%9901<<endl;
    return 0;
}
