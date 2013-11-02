/*
ID: haolink1
PROG: clocks
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

short ModuloAdd(short value){
    value=(value+3)%12;
    if(value == 0)
        return 12;
    else return value;
}

// 1        ABDE  0134
// 2        ABC 012
// 3        BCEF 1245
// 4        ADG 036
// 5        BDEFH 13457
// 6        CFI  258
// 7        DEGH 3467
// 8        GHI  678
// 9        EFHI 4578

void Move(short* clocks,short move,short* clocks_new){
    for(short i = 0; i < 9; i++){
        clocks_new[i] = clocks[i];
    }
    switch(move){
        case 1:
           clocks_new[0]=ModuloAdd(clocks[0]); 
           clocks_new[1]=ModuloAdd(clocks[1]); 
           clocks_new[3]=ModuloAdd(clocks[3]); 
           clocks_new[4]=ModuloAdd(clocks[4]);
           break;
        case 2:
           clocks_new[0]=ModuloAdd(clocks[0]); 
           clocks_new[1]=ModuloAdd(clocks[1]); 
           clocks_new[2]=ModuloAdd(clocks[2]); 
           break;
        case 3:
           clocks_new[1]=ModuloAdd(clocks[1]); 
           clocks_new[2]=ModuloAdd(clocks[2]); 
           clocks_new[4]=ModuloAdd(clocks[4]); 
           clocks_new[5]=ModuloAdd(clocks[5]); 
           break; 
        case 4:
           clocks_new[0]=ModuloAdd(clocks[0]); 
           clocks_new[3]=ModuloAdd(clocks[3]); 
           clocks_new[6]=ModuloAdd(clocks[6]); 
           break;
        case 5:
           clocks_new[1]=ModuloAdd(clocks[1]); 
           clocks_new[3]=ModuloAdd(clocks[3]); 
           clocks_new[4]=ModuloAdd(clocks[4]); 
           clocks_new[5]=ModuloAdd(clocks[5]); 
           clocks_new[7]=ModuloAdd(clocks[7]); 
           break;
        case 6:
           clocks_new[2]=ModuloAdd(clocks[2]); 
           clocks_new[5]=ModuloAdd(clocks[5]); 
           clocks_new[8]=ModuloAdd(clocks[8]); 
           break;
        case 7:
           clocks_new[3]=ModuloAdd(clocks[3]); 
           clocks_new[4]=ModuloAdd(clocks[4]); 
           clocks_new[6]=ModuloAdd(clocks[6]); 
           clocks_new[7]=ModuloAdd(clocks[7]); 
           break;
        case 8:
           clocks_new[6]=ModuloAdd(clocks[6]); 
           clocks_new[7]=ModuloAdd(clocks[7]); 
           clocks_new[8]=ModuloAdd(clocks[8]); 
           break;
        case 9:
           clocks_new[4]=ModuloAdd(clocks[4]); 
           clocks_new[5]=ModuloAdd(clocks[5]); 
           clocks_new[7]=ModuloAdd(clocks[7]); 
           clocks_new[8]=ModuloAdd(clocks[8]); 
           break;
    }
}

bool CheckMatch(short* clocks){
    for(short i =0; i < 9; i++){
        if(clocks[i] != 12)
            return false;
    }
    return true;
}
// using BFS algotithm in this problem is correct in theory,but it consume too much memory,because there are 
// so many nodes; We have to figure some way to alter the BFS so that it can meet the requirement.

int main(){
    ifstream fin("clocks.in");
    short* original = new short[9];
    for(int i = 0; i < 9; i++)
        fin >> original[i];
    short counter = 0;
    int table_num = 1;
    short* clocks_cur = original;
    short* clocks_next = 0;
    int i = 0;
    int j = 0;
    //BFS
    while(counter < 15){
        clocks_next = new short[table_num*9*9];
        for(i = 0; i < table_num; i++){
            for(j = 0; j < 9; j++){ 
                Move(clocks_cur+i*9,j+1,clocks_next+i*81+j*9); 
                if(CheckMatch(clocks_next+i*81+j*9)){
                    delete[] clocks_cur;
                    delete[] clocks_next;
                    goto BINGO;
                }
            }
        }
        table_num *= 9;
        delete [] clocks_cur;
        clocks_cur = clocks_next;
        counter++;
       cout<< counter<<" ";
    }
    if(counter >= 15){
        cout<<"missing"<<endl;
        return 0;
    }
BINGO:
    vector<int>selection;
    //format j
    j++;
    selection.push_back(j);
    int temp = 0;
    //format i
    i++;
    while(table_num > 1){
        temp = i % 9;
        if(temp == 0)
            temp = 9;
        selection.push_back(temp);
        i /= 9;
        if(temp != 9)
            i++;
        table_num /= 9;
    }
//    if(i>0){
//        //format i
//        i++;
//        //cout<< "i:"<<i<<" "<<"j:"<<j<<endl;  
//        int temp = 0;
//        while(i>9){
//            temp = i % 9;
//            if(temp == 0)
//                temp = 9;
//            selection.push_back(temp);
//            i /= 9;
//            if(temp != 9)
//                i++;
//        }
//        selection.push_back(i);
//    }
    ofstream fout("clocks.out");
    for(int len = selection.size()-1;len>0;len--){
        fout<<selection[len]<<" ";
    }
    fout<<selection[0]<<endl;
    return 0;
}
