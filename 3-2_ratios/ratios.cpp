/*
Main idea
Enumeration, because there are 100^3 cases;
Note the case where ratios may be 0;
*/
/*
ID: haolink1
PROG: ratios
LANG: C++
*/

//#include <iostream>
#include <fstream>

using namespace std;

int goal[3];
int items[3][3];
int ans[4];
const int INF = 1000;
int ComputeSum(int index, int i, int j, int k){
    return i*items[0][index] + j*items[1][index] + k*items[2][index];
}

int main(){
    ifstream fin("ratios.in");    
    ofstream cout("ratios.out");
    for(int i = 0; i < 3; i++){
        fin >> goal[i];
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            fin >> items[i][j];
        }
    }
    if(goal[0]+goal[1]+goal[2] == 0){
        cout <<"0 0 0 0"<<endl;
    }
    int min_sum = INF;
    for(int i = 0; i < 100 && i < min_sum; i++){
        for(int j  = 0; j < 100 && i + j < min_sum; j++){
            for(int k = 0; k < 100 && i + j + k < min_sum; k++){
                if(i + j + k == 0)
                    continue;
                int sum[3];
                for(int t = 0; t < 3; t++){
                    sum[t] = ComputeSum(t,i,j,k);
                }
                if(sum[0]*goal[1] != sum[1]*goal[0]) continue;//multiple can handle zero ratios;
                if(sum[1]*goal[2] != sum[2]*goal[1]) continue;
                if(sum[0] < goal[0] || sum[1] < goal[1] || sum[2] < goal[2]) continue;
                int total_sum = sum[0] + sum[1] + sum[2];
                min_sum = i + j + k;
                ans[0] = i;ans[1] = j;ans[2] = k; 
                ans[3] = total_sum /(goal[0]+goal[1]+goal[2]);
            }
        }
    }
    if(min_sum < INF)
        cout << ans[0] <<" "<< ans[1] <<" "<< ans[2] <<" "<< ans[3] << endl;
    else
        cout << "NONE" << endl;
    return 0;
}
