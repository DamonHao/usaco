/*
ID: haolink1
PROG: concom
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

const int com = 100;
short shares[com][com],final_shares[com][com];
bool  used[com][com];
//Main Idea:
//brute force;
//shares[i][j] is the initial shares company i own for company j;
//fianl_shares[i][j] is the shares company i own for j after calculate;
//used[i][j] == 1 denote i control j to avoid repeated computation;
int main(){
    ifstream fin("concom.in");
    int num = 0;
    fin >> num;
    int com_1 = 0; int com_2 = 0;
    for(int i = 0; i < num ; i++){
        fin >> com_1 >> com_2;
        fin >> shares[com_1-1][com_2-1];
        final_shares[com_1-1][com_2-1] = shares[com_1-1][com_2-1];
    }
    
    bool flag = 1;
    while(flag){
        flag = 0;
        for(int i = 0; i < com; i++){
            for(int j = 0; j < com; j++){
                if(used[i][j] == 0 && final_shares[i][j] > 50 && i != j){
                    //used[i][j] = used[j][i] = 1;
                    used[i][j] = 1;
                    flag = 1;
                    for(int k = 0; k < com; k++){
                        if(k != i && k != j)// now company i got company k's share that j own;
                            final_shares[i][k] += shares[j][k];
                    }
                }
            }
        }
    }
    flag = 1;
    ofstream fout("concom.out");
    for(int i = 0; i < com; i++){
        for(int j = 0; j < com; j++){
            if(final_shares[i][j] > 50 && i != j){
                fout<< i+1 <<" "<< j+1 << endl;
                flag = 0;
            }
        }
    }
    if(flag)
        fout << 0 << endl;
    return 0;
}
