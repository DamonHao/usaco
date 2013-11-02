/*
ID: haolink1
PROG: checker
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <time.h> 
using namespace std;
const short MAX = 13;
bool checkerboard[MAX][MAX];
short num = 0;
int counter = 0; 
bool unreset = true;
//short row = 0;
ofstream fout("checker.out");

void PrintSolution(){
    short i = 0;
    for(; i < num-1; i++){
        for(short j = 0; j < num; j++){
            if(checkerboard[i][j] == true)
                fout<<j+1 <<" "; 
        }
    }
    for(short j = 0; j < num; j++){
        if(checkerboard[i][j] == true){
            fout<< j+1 <<endl;
        } 
    }
}

void DFS(short row, short column){
    //Mark placement
    checkerboard[row][column] = true; 
    row++;
    if(row >= num){
        counter++;
        if(counter <= 3 && unreset){
            PrintSolution();  
        }
        return;
    }    
    for(short i = 0; i < num; i++){
        short column_1 = 0;
//        short column_2 = 0;
        for(short j = 0; j < row; j++){
            if(checkerboard[j][i]==true)
                goto label;
            //check left incline
            column_1 = i - (row -j);
            if(column_1 >= 0 && checkerboard[j][column_1] == true)
                goto label;
	    //check right incline
            column_1 = row + i - j;
            if(column_1 >= 0 && column_1 < num && checkerboard[j][column_1] == true){
                goto label;
            }
        }
        DFS(row,i);
        checkerboard[row][i] = false;
        label:;
    }
}

int main(){
     clock_t t;
     t = clock();
    ifstream fin("checker.in");
    fin >> num;
    if(num == 6){
        for(short column = 0; column < num; column++){
            DFS(0,column);
            checkerboard[0][column] = false;
        }
        fout << counter << endl;
        return 0;
    }
    short half_num = num/2;
    for(short column = 0; column < half_num; column++){
        DFS(0,column);
        checkerboard[0][column] = false;
    }
    if(num%2 == 0)
        fout << counter * 2 << endl;
    else{
        int cur_counter = counter;
        counter = 0;
        unreset = false;
        DFS(0,half_num);
        cur_counter = cur_counter*2 + counter;
        fout << cur_counter<<endl;
    }
    t = clock() - t;
    cout<<"Comsume time: "<<  ((float)t)/CLOCKS_PER_SEC <<endl;
    return 0;
}
