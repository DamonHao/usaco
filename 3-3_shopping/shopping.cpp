/*
Main idear
DP problem. Take each offer as a single choise for DP.
dp[a1][a2][a3][a4][a5] = min{dp[a1-prodcut_num[i][1]][a2-prodcut_num[i][2]]
                        [a1-prodcut_num[i][3]][a1-prodcut_num[i][4]][a1-prodcut_num[i][5]] + product_num[i][0]}
ak - product_num[i][k] >= 0;  1 <= i <= offers_num;
boundary conditions: dp[0][0][0][0][0] = 0;

dp[a1][a2][a3][a4][a5] denote the least money we cost to buy a1 product 1, a2 product 2 .... a5 product 5;
product[i][1] if i >= 1, it denote the number of product 1 in offer i; if i == 0; it denote the reduced price
of offer i;
*/
/*
Executing...
   Test 1: TEST OK [0.000 secs, 3536 KB]
   Test 2: TEST OK [0.000 secs, 3536 KB]
   Test 3: TEST OK [0.000 secs, 3536 KB]
   Test 4: TEST OK [0.011 secs, 3536 KB]
   Test 5: TEST OK [0.011 secs, 3536 KB]
   Test 6: TEST OK [0.000 secs, 3536 KB]
   Test 7: TEST OK [0.000 secs, 3536 KB]
   Test 8: TEST OK [0.000 secs, 3536 KB]
   Test 9: TEST OK [0.011 secs, 3536 KB]
   Test 10: TEST OK [0.022 secs, 3536 KB]
   Test 11: TEST OK [0.032 secs, 3536 KB]
   Test 12: TEST OK [0.032 secs, 3536 KB]

All tests OK.
*/
/*
ID: haolink1
PROG: shopping
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int dp[6][6][6][6][6];
int product_num[105][6];
int product_code[1000];//product_code[i] denote product i 's code by the order they are encountered;
int ori_mark = 0;
int buy_num[6];
int offers_num = 0;
ifstream fin("shopping.in");
ofstream cout("shopping.out");
inline int Min(int a,int b){
    return a <= b ? a : b;
}
// Easy to code and only compute the necessary element of dp[]..[]; 
int Memorized_DP(int a1,int a2, int a3,int a4,int a5){
    if(dp[a1][a2][a3][a4][a5] != ori_mark)
        return dp[a1][a2][a3][a4][a5];
    int min_price = ori_mark,w1,w2,w3,w4,w5;
    for(int i = 1; i <= offers_num; i++){
        w1 = a1 - product_num[i][1];
        w2 = a2 - product_num[i][2];
        w3 = a3 - product_num[i][3];
        w4 = a4 - product_num[i][4];
        w5 = a5 - product_num[i][5];
        if(w1 < 0 || w2 < 0 || w3 < 0 || w4 < 0 || w5 < 0) continue;
        if(dp[w1][w2][w3][w4][w5] == ori_mark)
            dp[w1][w2][w3][w4][w5] = Memorized_DP(w1,w2,w3,w4,w5);  
        if(min_price > dp[w1][w2][w3][w4][w5]+product_num[i][0]){
            min_price = dp[w1][w2][w3][w4][w5]+product_num[i][0]; 
        }
    } 
    return min_price; 
}

int main(){
    //init
    int s = 0, num = 0, c = 0, k = 0, code = 0, b = 0;
    fin >> s; 
    for(int i = 1; i <= s; i++){
        fin >> num;
        for(int j = 0; j < num; j++){
            fin >> c >> k;
            if(product_code[c] == 0) product_code[c] = ++code;
            product_num[i][product_code[c]] = k;
        }
        fin >> product_num[i][0];
    }
    fin >> b;
    offers_num = s + b;
    //Single product can also be regarded as a offer.
    for(int i = 1; i <= b; i++){
        fin >> c >> k;
        if(product_code[c] == 0) product_code[c] = ++code;
        product_num[s+i][product_code[c]] = 1;
        buy_num[product_code[c]] = k;
        fin >> product_num[s+i][0];
    }
    //Note give each element of dp[][][][][] a big enough initial value 
    //except dp[0][0][0][0][0], because finally what we want is exactly 
    //a1,a2,a3,a4,a5 for dp[a1][a2][a3][a4][a5];
    memset(dp,0xF,sizeof(dp));
    ori_mark = dp[0][0][0][0][0];
    dp[0][0][0][0][0] = 0;
    //DP 
    cout << Memorized_DP(buy_num[1],buy_num[2],buy_num[3],buy_num[4],buy_num[5]) << endl;
    return 0;
}

