/*
ID: haolink1
PROG: palsquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
using namespace std;

typedef unsigned int u_int;

string num_map[] = {"A","B","C","D","E","F","G","H","I","J","K"};
//Transform demical to the value on target base,and then covert target value into 
//string in reverse order.
void TransformBase(u_int base,u_int original_value,vector<string>& target_value){
    stringstream temp;
    u_int remainder = 0;
    while(original_value >= base){
        remainder =  original_value % base;
        if(remainder < 10){
            temp << remainder;  
            target_value.push_back(temp.str());
            temp.str("");//clear up the content of temp
        }else{
            target_value.push_back(num_map[remainder-10]);
        }
        original_value /= base;
    }
    remainder = original_value % base;
    if(remainder < 10){
        temp << remainder;  
        target_value.push_back(temp.str());
    }else{
        target_value.push_back(num_map[remainder-10]);
    }
}

bool IsPalindromic(vector<string>& value){
    u_int len = value.size();
    for(u_int i = 0; i < len/2; i++){
        if(value[i].compare(value[len-1-i]) != 0)
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
        vector<string> target_value;
        TransformBase(base,i*i,target_value);
        if(IsPalindromic(target_value)){ 
            vector<string> value;
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
