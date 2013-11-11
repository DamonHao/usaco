/*
ID: haolink1
PROG: subset
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int max_num = 0;
unsigned long ans[40][40*(40+1)/2];
//Main Idea
//Dynamic Programming.This problem is variant of 0-1 knapsack problem.
// ans[i][j] means the subset number whose sum is j for the set {1,2,..,i};
int main(){
    ifstream fin("subset.in");
    fin >> max_num;
    int sum = max_num*(max_num+1)/2;
    ofstream fout("subset.out");
    //The sum of set must be exactly divided by 2 if the sums of both subsets are identical;
    if(sum % 2 != 0){
        fout<<0<<endl;
        return 0;
    }
    int half_sum = sum/2;
    ans[1][1] = 1;
    for(int i = 2; i <= max_num; i++){
        for(int j = 1; j <= half_sum; j++){
            if(j < i) ans[i][j] = ans[i-1][j];
            if(j == i) ans[i][j] = ans[i-1][j]+1;
            if(j > i) ans[i][j] = ans[i-1][j]+ans[i-1][j-i];
        }
    }
    fout<<ans[max_num][half_sum]/2<<endl;
    return 0;
}



