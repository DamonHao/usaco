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
ofstream fout("checker.out");

bool CheckValid(short row,short column){
    //Check column
    for(short j = 0; j < row; j++){
        if(checkerboard[j][column]==true)
            return false;
    }
    //check left incline
    short row_1 = row-1 ;
    short column_1 = column-1;
    while(row_1 >= 0 && column_1 >=0){
        if(checkerboard[row_1][column_1] == true)
            return false;
        row_1--;
        column_1--;
    }
    //check right incline
    row_1 = row -1;
    column_1 = column + 1;
    while(row_1 >= 0 && column_1 < num){
        if(checkerboard[row_1][column_1] == true)
            return false;
        row_1--;
        column_1++;
    }
    return true;
}

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
    //Mark place 
    checkerboard[row][column] = true; 
    row++;
    if(row >= num){
        counter++;
        if(counter <= 3){
            PrintSolution();  
        }
        return;
    }    
    for(short i = 0; i < num; i++){
        if(CheckValid(row,i)){
            DFS(row,i);
            //Unmark palce
            checkerboard[row][i] = false;
        }
    }
}

int main(){
    time_t timer_begin;
    time(&timer_begin);
    ifstream fin("checker.in");
    fin >> num;
    for(short column = 0; column < num; column++){
        DFS(0,column);
        //
        checkerboard[0][column] = false;
    }
    fout << counter << endl;
    time_t timer_end;
    time(&timer_end);
    cout<<"Comsume time: "<<timer_end -timer_begin<<endl;
    return 0;
}
