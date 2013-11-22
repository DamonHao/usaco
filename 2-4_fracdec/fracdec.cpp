/*
ID: haolink1
PROG: fracdec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include<cstring>
using namespace std;

char result[100000];
int position[100000];

int IntegerPart(int a){
    if(a == 0)
        return 1;
    int i = 0;
    while(a){
        a /= 10;
        i++;
    }
    return i;
}

// Main idea
// mimic the division process; During this process, we record the  
// remainder. If the one remainder have appeared before, then the the decimal 
// representation has a repeating sequence of digits. 
// Use result[] to record the quotient
// Assume n is remainder and use position[n] to record the index of quotient in result[]
int main(){
    int N = 0;
    int D = 1;
    int tmp,index,tmp_m;
    bool flag = 0;
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");
    fin >> N >> D;
    if(N%D == 0){
        fout<<N/D<<".0"<<endl;
    }else{
        //Handle the integer digits
        tmp = N/D;
        index = IntegerPart(tmp);
        for(int i = index-1; i >= 0; i--){
            tmp_m = tmp%10; 
            result[i] = '0' + tmp_m;
            tmp /= 10;
        }
        result[index++] = '.';
        //Handle the digits after decimal point
        memset(position,-1,sizeof(position));
        while(1){
            tmp_m = N % D; 
            if(tmp_m == 0){
                break;
            }else if(position[tmp_m] != -1){
                flag = 1;
                break;
            }
            tmp = tmp_m * 10/D;
            position[tmp_m] = index;
            result[index++] = '0' + tmp;
            N = tmp_m*10;
        }
        if(flag){//Handle repeating sequence
            int m = position[tmp_m]; 
            for(int i = index-1; i >= m; i--){
                result[i+1] = result[i];
            }
            result[m] = '(';
            result[++index] = ')';
            index++;
        }
        //test output format
//        index = 152;
//        for(int i = 0; i < 153; i++){
//            result[i] = '1';
//        }

        int counter = 0;
        for(int i = 0; i < index; i++){
            fout << result[i];
            counter++;
            if(counter % 76 == 0){
                counter = 0;
                fout<<endl;
            }
        }
        if(counter % 76 != 0)
            fout<<endl;
    }
    return 0;
}

