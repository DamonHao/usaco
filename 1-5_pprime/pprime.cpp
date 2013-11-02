/*
ID: haolink1
PROG: pprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

ofstream fout("pprime.out");

bool IsPrime(int num){
    int temp = sqrt(num);
    for (int i = 2; i <= temp; i++){
        if(num%i==0)
            return false;
    }
    return true;
}

void CheckValid(int begin,int end,int target_num){
    if(target_num >= begin && target_num <= end && IsPrime(target_num))
        fout << target_num <<endl;
}
// For this problem, the usaco give two hint:
// 1 Generate the palindromes and see if they are prime.
// 2 Generate palindromes by combining digits properly. You might need more than one of the loops like below.
///* generate five digit palindrome: */
//for (d1 = 1; d1 <= 9; d1+=2) {  /* only odd; evens aren't so prime */
//    for (d2 = 0; d2 <= 9; d2++) {
//        for (d3 = 0; d3 <= 9; d3++) {
//            palindrome = 10000*d1 + 1000*d2 +100*d3 + 10*d2 + d1;
//            ... deal with palindrome ...
//        }
//    }
//}

//Use this two hint, we can found 
//If a number can be divided exactly by 11, after the sum of its odd digts minus the sum of its even 
//digits, the difference can be divided exactly by 11.Eg: 1234567, sum of odd digits 1+3+5+7=16
//sum of even digits : 2+4+6=12, 16 -12 = 4, which can't be devided by 11, that is 1234567 can't be
//devided by 11.
//Considering even palindromes,from above conclusion, it should be devided by 11 exactly,which means they
//can't be prime,like 135531, except 11.
//Considering odd palindromes, we can construct them by the form like: a*10001+b*1010+c*100 
//during enumerating a,b,c..., we find "a" should not be a even value, otherwise, the whole number isn't prime.
int main(){
    ifstream fin("pprime.in");
    int begin = 0;
    int end = 0;
    fin >> begin;
    fin >> end;
    //Handle special case
    if(begin == 5) fout << 5 <<endl;
    if(begin <= 7 && end >= 7) fout << 7 <<endl;
    if(begin <= 11 && end >= 11) fout << 11 <<endl;
    //Handle regular case;
    if(begin <= 999 && end >= 101){
        for(short a  = 1; a <= 9; a+=2){
            for(short b = 0; b <= 9; b++){
                CheckValid(begin,end,a*101+b*10);
            }
        }
    }
    if(begin <= 99999 && end >= 10001){
        for(short a = 1; a <= 9; a+= 2){
            for(short b = 0; b <= 9; b++){
                for(short c = 0; c <= 9; c++){
                    CheckValid(begin,end,a*10001+b*1010+c*100);
                }
            }
        }
    }
    if(begin <= 9999999 && end >= 1000001){
        for(short a = 1; a <= 9; a+= 2){
            for(short b = 0; b <= 9; b++){
                for(short c = 0; c <= 9; c++){
                    for(short d = 0; d <=9; d++ ){
                        CheckValid(begin,end,a*1000001+b*100010+c*10100+d*1000);
                    }
                }
            }
        }
    } 
    return 0;
}
