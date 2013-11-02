/*
ID: haolink1
PROG: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;
//Use global varible to reduce the function DFS's aguments
const short  max_value = 20;
bool bucket_state[max_value+1][max_value+1];
short a_capacity = 0;
short b_capacity = 0;
short c_capacity = 0;
bool c_remain[max_value+1] = {false}; 
short Max(short first,short second){
    if(first >= second)
        return first;
    else return second;
}

short Min(short first,short second){
    if(first <= second)
        return first;
    else return second;
}
void DFS(short a,short b,short c){
    if(bucket_state[a][b] == true)
        return;
    bucket_state[a][b] = true;
    if(a == 0)
       c_remain[c] = true; 
    //There are total 6 cases to pour bucket.Once pouring begin,it won't end unless
    //either the soucr bucket is empty or the target bucket is full.
    //a->b
    if(a > 0 && b < b_capacity)
        DFS(Max(0,a+b-b_capacity),Min(b_capacity,a+b),c);
    //a->c
    if(a > 0 && c < c_capacity)
        DFS(Max(0,a+c-c_capacity),b,Min(c_capacity,a+c));
    //b->a
    if(b > 0 && a < a_capacity)
        DFS(Min(a_capacity,a+b),Max(0,a+b-a_capacity),c);
    //b->c
    if(b > 0 && c < c_capacity)
        DFS(a,Max(0,b+c-c_capacity),Min(c_capacity,b+c));
    //c->a
    if(c > 0 && a < a_capacity)   
        DFS(Min(a_capacity,a+c),b,Max(0,a+c-a_capacity));
    //c->b
    if(c > 0 && b < b_capacity)
        DFS(a,Min(b_capacity,b+c),Max(0,b+c-b_capacity));
}

int main(){
    ifstream fin("milk3.in");
    fin >> a_capacity;
    fin >> b_capacity;
    fin >> c_capacity;
    for(short i = 0; i < max_value; i++){
        for(short j = 0; j < max_value; j++){
            bucket_state[i][j] = false;
        }
    }
    DFS(0,0,c_capacity);
    ofstream fout("milk3.out");
    for(short i = 0; i < c_capacity; i++){
        if(c_remain[i] == true)
            fout << i <<" ";
    }
    // c_capacity is always qualified;
    fout<<c_capacity<<endl;
}
