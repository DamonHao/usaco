/*
ID: haolink1
PROG: palsquare
LANG: C++
*/
//#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef unsigned int u_int;

char num_map[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K'};
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

int main(){
    ifstream fin("palsquare.in");
    u_int base;
    fin >> base;
    ofstream fout("palsquare.out");
    for(u_int i = 1; i <= 300; i++){
        vector<char> target_value;
        TransformBase(base,i*i,target_value);
        if(IsPalindromic(target_value)){ 
            vector<char> value;
            TransformBase(base,i,value);
            for(int j = value.size()-1; j >= 0; j--)
                fout<<value[j];
            fout<<" ";
            for(int j = target_value.size()-1; j >= 0; j--)
                fout<<target_value[j]; 
            fout<<endl;
        }
    }
}
