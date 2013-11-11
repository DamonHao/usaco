/*
ID: haolink1
PROG: preface
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
//I 1,V 5,X 10,L 50,C 100,D 500,M 1000;
int letters_counter[7] = {0};
char letters[] ={'I','V','X','L','C','D','M'}; 
void Handle_1_To_9(short number,short digit);

//Main Idea:
//Number form 1 to 9 in each digit compose of fixed letters;
//For example
//6 is VI,60 is CL,and 600 is DC; 
int main(){
    ifstream fin("preface.in");
    int max_num = 0;
    fin >> max_num;
    short remainer = 0;
    short cur_value = 0;
    for(short i = 1; i <= max_num; i++){
        cur_value = i;
        short digit = 0;
        while(cur_value > 0){
            remainer = cur_value % 10;     
            if(remainer > 0)
                Handle_1_To_9(remainer,digit);    
            cur_value /= 10;
            digit+=2;
        }
    }
    ofstream fout("preface.out");
    for(short i = 0; i < 7; i++){
        if(letters_counter[i] > 0)
            fout<<letters[i]<<" "<<letters_counter[i]<<endl;
    }
    return 0;
}

void Handle_1_To_9(short value,short digit){
    switch(value){
        case 1: 
           letters_counter[0+digit]++;
           break;
        case 2:
            letters_counter[0+digit]+=2;
            break;
        case 3:
            letters_counter[0+digit]+=3;
            break;
        case 4:
            letters_counter[0+digit]++;
            letters_counter[1+digit]++;
            break;
        case 5:
            letters_counter[1+digit]++;
            break;
        case 6:
            letters_counter[0+digit]++;
            letters_counter[1+digit]++;
            break;
        case 7:
            letters_counter[0+digit]+=2;
            letters_counter[1+digit]++;
            break;
        case 8:
            letters_counter[0+digit]+=3;
            letters_counter[1+digit]++;
            break;
        case 9:
            letters_counter[0+digit]++;
            letters_counter[2+digit]++;
            break;
    }
}
