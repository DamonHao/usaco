/*
ID: haolink1
PROG: zerosum
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

int num = 0;
ofstream fout("zerosum.out");

void DFS(char* str,int depth);
bool IsZeroSum(char* str);
//Main Idea:
//Search by DFS;
//In ASCII order means that cout the sum of string's ASCII value, and sort
//them in ascending order;
int main(){
    ifstream fin("zerosum.in");    
    fin >> num;
    char str[] = "1 2 3 4 5 6 7 8 9";
    //truncate string to only have first n numbers
    str[2*num-1] = '\0';
    DFS(str,0);
    return 0;
}

void DFS(char* str,int depth){
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

bool IsZeroSum(char* str){
    int sum = 0;
    int cur_value = 0;
    int sign = 1; 
    for(char* p = str; *p ; p++){
        switch(*p){
            case ' ':
                break;
            case '+':
            case '-':
                sum += sign*cur_value;
                sign = *p == '+' ? 1 : -1;
                cur_value = 0;
                break;
            default:
                cur_value = cur_value*10 + *p - '0';
        } 
    }
    sum += sign*cur_value;
    return !sum;
}
