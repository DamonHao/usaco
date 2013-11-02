/*
ID: haolink1
PROG: sprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>    // std::sort
using namespace std;

short sprime_len = 0;
ofstream fout("sprime.out");
vector<int> sprimes;
bool IsPrime(int num){
    int temp = sqrt(num);
    for (int i = 2; i <= temp; i++){
        if(num%i==0)
            return false;
    }
    return true;
}

void DFS(int value,int weight,short counter){
    counter++;
    if(counter > sprime_len){
        //fout << value << endl; 
        sprimes.push_back(value);
        return;
    }
    for(int i = 1; i <= 9; i+=2){
        int temp = value* weight + i;
        if(IsPrime(temp))
            DFS(temp,weight,counter);
    }
}
bool CompareValue(int first,int second){
    if(first <= second)
        return true;
    else return false;
}
int main(){
    ifstream fin("sprime.in");
    fin >> sprime_len;
    DFS(2,10,1);
    for(int i = 3; i <= 7; i+=2){
        DFS(i,10,1); 
    }
    sort(sprimes.begin(),sprimes.end(),CompareValue);
    for(unsigned int i = 0; i < sprimes.size(); i++){
        fout << sprimes[i] << endl;
    }
    return 0;
}

