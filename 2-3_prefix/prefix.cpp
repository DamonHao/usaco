/*
ID: haolink1
PROG: prefix
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
//Note add 1 element for the case like 
// match_str_len[199999] = Max(match_str_len[199999],match_str_len[199999+1]+1) 
int match_str_len[200001];
int Max(int a, int b);

//Main Idea:
//Dynamic Programming
//For String srt which length is len,
//match_str_len[i] means the max len prefix of str[i...len-1];
//DP state transition equation:
//If str[i...i+primitive_len] match some primitive from set Primitives;
//Then match_str_len[i] = Max(match_str_len[i], match_str_len[i+primitive_len]+primitive_len); 
//So we compute  match_str_len[] from match_str_len[len-1] to match_str_len[0] which is final answer;
int main(){
    ifstream fin("prefix.in");
    ifstream test;
    vector<string> primitives;
    string str;
    fin>>str;
    while(str != "." ){
        primitives.push_back(str);
        fin>>str;
    }
    string target_str;
    //fin>>str;
    while(fin>>str){
        target_str += str;
        //fin >> str;
    }
    //cout<<target_str<<endl;
    int target_len = target_str.length();
    int primitives_len = primitives.size();
    for(int i = target_len-1; i >= 0; i--){
        for(int j = 0; j < primitives_len; j++){
            int primitive_len = primitives[j].size(); 
            if((i+primitive_len <= target_len) && (target_str.compare(i,primitive_len,primitives[j]) == 0))
                match_str_len[i] = Max(match_str_len[i], match_str_len[i+primitive_len]+primitive_len);
        }
    }
    ofstream fout("prefix.out");
    fout<<match_str_len[0]<<endl;
    return 0;
}

int Max(int a, int b){
    if(a >= b)
        return a;
    else return b;
}
