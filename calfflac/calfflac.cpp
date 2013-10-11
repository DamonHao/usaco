/*
ID: haolink1
PROG: calfflac
LANG: C++
*/

#include <iostream>
#include <fstream>
//#include <vector>
#include <string>
using namespace std;

typedef unsigned int u_int;

bool IsEqual(char first,char second){
    if(first == second || first + 32 == second || first == second +32)
        return true;
    else 
        return false;
}

bool IsValid(char target){
    if((target >= 65 && target <= 90) || (target >= 97 && target <= 122))
        return true;
    else 
        return false;
}
int main(){
    ifstream fin("calfflac.in");
    char total_string[20000];
    //read all the file data form stream into char array;
    fin.read(total_string,20000);
    int pal_begin = 0;
    int pal_end = 0;
    int max_pal_len = 1;
    int total_len = fin.gcount();
    // found odd palindromes and the core character of the palindromes must be valid,
    // begin with position 1
    for(int i = 1; i < total_len-1; i++){
        if(!IsValid(total_string[i]))// the core character of the palindromes must be valid, 
            continue;
        int temp_pal_len = 1;
        int forward = i-1;
        int backward = i+1;
        while(true){
            while(forward >= 0){
                if(IsValid(total_string[forward]))
                    break;
                else
                    forward--;
            }
            while(backward < total_len){
                if(IsValid(total_string[backward]))
                    break;
                else
                    backward++;
            }
            if(forward < 0 || backward >= total_len)
                break;
            if(IsEqual(total_string[forward],total_string[backward])){
                temp_pal_len+=2;
                if(temp_pal_len > max_pal_len){
                    pal_begin = forward;
                    pal_end = backward;
                    max_pal_len = temp_pal_len;
                }
                forward--;
                backward++;
            }else{
                break;
            }
        }
    }        
    //find even palindromes 
    for(int i = 1; i < total_len-1; i++){
        if(!IsValid(total_string[i]))// the core character of the palindromes must be valid,
            continue;
        int temp_pal_len = 0;
        int forward = i;
        int backward = i+1;
        while(true){
            while(forward >= 0){
                if(IsValid(total_string[forward]))
                    break;
                else
                    forward--;
            }
            while(backward < total_len){
                if(IsValid(total_string[backward]))
                    break;
                else
                    backward++;
            }
            if(forward < 0 || backward >= total_len)
                break;
            if(IsEqual(total_string[forward],total_string[backward])){
                temp_pal_len+=2;
                if(temp_pal_len > max_pal_len){
                    pal_begin = forward;
                    pal_end = backward;
                    max_pal_len = temp_pal_len;
                }
                forward--;
                backward++;
            }else{
                break;
            }
        }
    }
    ofstream fout("calfflac.out");
    fout<< max_pal_len <<endl;
    string result(total_string+pal_begin,pal_end - pal_begin +1);
    fout << result << endl;
}
