/*
F[i] denote the 5 digits from rightmost non-zero digit of i! ;
There is a trap, we can't just store the rightmost non-zero digit of i!
Eg: 15 * 2 = 30 may affect the second last digit;
Since N is 4220 at most, we should store 5 digits;
*/
/*
ID: haolink1
PROG: fact4
LANG: C++
*/

//#include <iostream>
#include <fstream>
using namespace std;
int F[4221];
int limit = 100000; 
int main(){
    ifstream fin("fact4.in");
    ofstream cout("fact4.out");
    int N = 0;
    fin >> N;
    F[1] = 1;
    int i = 1;
    while(i < N){
        i++;
        int tmp = F[i-1] * i;
        int remain = tmp % 10;
        while(!remain){
            tmp /= 10;
            remain = tmp%10;
        }
        F[i] = tmp % limit;
    } 
    cout << F[N] % 10<< endl;
    return 0;
}

