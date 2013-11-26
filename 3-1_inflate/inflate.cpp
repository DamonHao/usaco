/*
ID: haolink1
PROG: inflate
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int cost[10000];
int weight[10000];
int f[10001];

//Main idea:
//Dynamic Programming 
//f[i][j] = max{f[i-1][j],f[i][j-cost[i]]+weight[i]}; 
//f[i][j] denote the max sum of weights(in this case, that is points) 
//from the first i categories(start from 0),with capacity j; 
//To save space, we change it to
//f[j] = max{f[j],f[j-cost[i]]+weight[i]}; if j >= cost[i];
//This problem is a variant of 01 knapsack problem, called CompletePack.
int main(){
    int M = 0;
    int N = 0;
    ifstream fin("inflate.in");
    fin >> M >> N;
    for(int i = 0; i < N; i++){
        fin >> weight[i] >> cost[i];
    }
    for(int i = 0; i < N; i++){
        for(int j = cost[i]; j <= M; j++){
            f[j] = max(f[j],f[j-cost[i]]+weight[i]);
        }
    }
    ofstream fout("inflate.out");
    fout << f[M] << endl;
    return 0;
}
