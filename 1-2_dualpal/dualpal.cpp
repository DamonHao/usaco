/*
ID: haolink1
PROG: dualpal
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef unsigned int u_int;
char num_map[] = {'0','1','2','3','4','5','6','7','8','9'};

//Transform demical to the value on target base,and then covert target value into 
//string in reverse order.
void TransformBase(u_int base,u_int original_value,vector<char>& target_value){
    while(original_value >= base){
        target_value.push_back(num_map[original_value % base]);
        original_value /= base;
    }
    target_value.push_back(num_map[original_value % base]);
}

bool IsPalindromic(vector<char>& value){
    u_int len = value.size();
    for(u_int i = 0; i < len/2; i++){
        if(value[i] != value[len-1-i])
            return false;
    }
    return true;
}

bool PalindromicInTwoOfBase(u_int value){
    char pal_count = 0;
    for(u_int i = 2; i <= 10; i++){
        vector<char> target_value;
        TransformBase(i,value,target_value);
        if(IsPalindromic(target_value))
            pal_count++;
        if(pal_count >= 2)
            return true;
    }
    return false;
}

int main(){
    ifstream fin("dualpal.in");
    u_int required_num, basic_num;
    fin >> required_num;
    fin >> basic_num;
    u_int count = 0;
    basic_num++;
    ofstream fout("dualpal.out");
    while(count < required_num){
        if(PalindromicInTwoOfBase(basic_num)){
            fout<<basic_num<<endl;
            count++;
        }
        basic_num++;
    }
    return 0;
}
