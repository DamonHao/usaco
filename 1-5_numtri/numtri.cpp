/*
ID: haolink1
PROG: numtri
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
const short max_row = 1000;
int numbers[max_row][max_row];

int Max(int first,int second){
    if(first >= second)
        return first;
    return second;
}
//Note: the key point of this problem is you shoud add the vlaue of number
//triangle from bottom to top, then you can see the optimal substructure.
//So you can try DP(dynamic programming),and that's it!
int main(){
    ifstream fin("numtri.in");
    short row_num = 0;
    fin >> row_num;
    for(short i = 0; i < row_num; i++){
        for(short j = 0; j <= i; j++){
            fin >> numbers[i][j];
        }  
    }
    for(int i = row_num-2; i >=0; i--){
        for(int j = 0; j <= i; j++){
            //optimal substucture
            numbers[i][j] = Max(numbers[i+1][j],numbers[i+1][j+1])+numbers[i][j]; 
        }
    }
    ofstream fout("numtri.out");
    fout<<numbers[0][0]<< endl;
    return 0;
}

