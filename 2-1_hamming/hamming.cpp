/*
ID: haolink1
PROG: hamming
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

short bit_num= 0;
short min_distance = 0 ;

short CountDistance(short element1,short element2);
bool CheckValid(vector<short>& selected_codewords,short codeword);

//Main Idea
//We use the greedy algorithm and start to check the hamming distance of nummber from
//the minimun num.The pity is that I can't prove the correctness of it.I will try it later.
int main(){
    ifstream fin("hamming.in");
    short codewords_num = 0;
    fin >> codewords_num >> bit_num >> min_distance;
    short max_value = (1 << bit_num);
//    for(short i = 0; i < bit_num; i++){
//        max_value *= 2;
//    }
    vector<short> selected_codewords;
    // 0 can be one of the numbers in the set, because if the minimum number in the set
    // were N instead of 0, we could XOR N to each number in the set and they would 
    //still be the same distance apart.
    selected_codewords.push_back(0);
    //Note the counter start form 1;
    short counter = 1;
    //Start from minimun number;
    for(short i = 1; i <= max_value; i++){
        if(CheckValid(selected_codewords,i)){
            selected_codewords.push_back(i);
            counter++;
        }
        if(counter >= codewords_num)
            break;
    }
    ofstream fout("hamming.out");
    //Note the ouput format;
    short print_num = 0;
    short len = selected_codewords.size();
    for(short i = 0; i < len-1; i++){
        if(print_num < 9){
            fout<<selected_codewords[i]<<" ";
            print_num++;
        }else{
            fout<<selected_codewords[i]<<endl;
            print_num = 0;
        }
    }
    if(len > 0)
        fout<<selected_codewords[len-1]<<endl;
    return 0;
}

short CountDistance(short element1,short element2){
    short distance = 0;
    short diff = element1 ^ element2;
    for(short i = 0; i < bit_num; i++){
        if((1<<i)& diff)
            distance++;
    }
    return distance;
}

bool CheckValid(vector<short>& selected_codewords,short codeword){
    for(short i = 0; i < short(selected_codewords.size());i++){
       if(CountDistance(selected_codewords[i],codeword) < min_distance)
           return false;
    }
    return true;
}
