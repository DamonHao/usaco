/*
ID: haolink1
PROG: kimbits
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int main(){
    int N = 0,L = 0,I = 0;
    ifstream fin("kimbits.in");
    fin >> N >> L >> I;
    long long i = 0;
    int cur_value = 0;
    int len = 0;
    while(i < I){
        do{
            len = 0;
            for(short j = 0; j < N; j++){
                if(cur_value & (1<<j))
                    len++;
            }
            cur_value++;
        }while(len > L);
        i++;
    }
    cout << cur_value -1 << endl;
    return 0;
}
