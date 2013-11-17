/*
ID: haolink1
PROG: zerosum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int num = 0;
ofstream fout("zerosum.out");

void DFS(string& str,int depth);
bool IsZeroSum(string& str);
//Main Idea:
//Search by DFS;
//In ASCII order means that cout the sum of string's ASCII value, and sort
//them in ascending order;
int main(){
    ifstream fin("zerosum.in");    
    fin >> num;
    string str = "1 2 3 4 5 6 7 8 9";
    DFS(str,0);
    return 0;
}

void DFS(string& str,int depth){
    if(depth == num-1){
        if(IsZeroSum(str)){
           for(int i = 0; i < 1+(num-1)*2; i++){
                fout<<str[i];
           }
           fout<<endl;
        }
        return;
    }
    char *p;
    for(p = " +-"; *p; p++){
        str[1+depth*2] = *p;
        DFS(str,depth+1);
    }
}

bool IsZeroSum(string& str){
    int valid_len = 1 + (num-1)*2;
    int sum = 0;
    int cur_value = str[0] - '0';
    int former_operator = -1;
    for(int i = 1; i < valid_len; i+=2){
        switch(str[i]){
            case ' ':
                cur_value = cur_value * 10 + str[i+1] -'0';
                break;
            case '+':
            case '-':
                //set former_operator == -1 for the first time "+/-" is met;
                if(str[former_operator] == '+' || former_operator == -1)
                    sum += cur_value;
                else if(str[former_operator] == '-')
                    sum -= cur_value;
                former_operator = i;
                cur_value = str[i+1] - '0';
                break;
        } 
    }
    //Note remmenber to check for the last operator "+/-"
    //set former_operator == -1 for the case no "+/-" in str;
    if(str[former_operator] == '+' || former_operator == -1)
        sum += cur_value;
    else if(str[former_operator] == '-')
        sum -= cur_value;
    return !sum;
}
