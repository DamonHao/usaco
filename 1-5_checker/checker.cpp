/*
ID: haolink1
PROG: checker
LANG: C++
*/

#include <iostream>
#include <fstream>
//#include <time.h> 
using namespace std;
const short MAXN = 13;
//Record the column placement in each row.
short row_record[MAXN]={0};
//The below three arrays record checker's placement info which is used to check whether the
//later checker's placement meet the requirement.This is the key point to redcue the running time.
//Record the the number of checker in column j 
//(i, j) -> j
char col_mark[MAXN] = {0};        
//Record the number of checker in up-diagonal of (i,j)
//(i, j) -> i+j 
char updiag[2*MAXN] = {0};
//Record the number of checker in the down-diagonal of (i,j)  
//(i, j) -> i-j + N
char downdiag[2*MAXN] = {0};
//A single integer N (6 <= N <= 13) that is the dimension of the N x N checkerboard
short num = 0;
//Count the solution's number.
int counter = 0; 
//Record the printed solutions' number 
char print_solution_num = 0;
ofstream fout("checker.out");

void PrintSolution(){
    short i = 0;
    for(; i < num-1; i++){
        fout<<row_record[i]+1 <<" "; 
    }
    fout<<row_record[i]+1 <<endl;
}

void DFS(short row, short column){
    //Mark placement
    row_record[row] = column;
    col_mark[column]++;
    updiag[row+column]++;
    downdiag[row-column+num]++;
    //increase row
    row++;
    if(row >= num){
        counter++;
        if(print_solution_num < 3){
            print_solution_num++;
            PrintSolution();
        } 
        return;
    }    
    for(short column_1 = 0;  column_1 < num; column_1++){
        //check
        if(!col_mark[column_1] && !updiag[row+column_1] && !downdiag[row-column_1+num]){
            DFS(row,column_1);   
            //Unmark placement
            col_mark[column_1]--;
            updiag[row+column_1]--;
            downdiag[row-column_1+num]--;
        }
    }
}
//Note: This problem is the same wiht "Egiht Queen" problem, which is a classic DFS problem
//But if you use DFS directly, you can't meet the time requirement "1 CPU second"
//Since when you find one solution, its reflection is another solution.
//If the 'num' is even, you can search the first (num/2)-1 placement in the first row
//and get solution number sum1 .Then the total_s0lution = 2 * sum1;
//If the 'num' is even, you can search the first (num/2)-1 and get sum1.Then you compute the
//slolution in placement num/2 and get sum2, the total_solution = 2*sum1 + sum2;
int main(){
//     clock_t t;
//     t = clock();
    ifstream fin("checker.in");
    fin >> num;
    //num == 6 is a special case, because the its first (num/2)-1 placement's solution is 2,that 
    //can't pirnt 3 solutions.
    if(num == 6){
        for(short column = 0; column < num; column++){
            DFS(0,column);
            //Unmark the placement
            col_mark[column]--;
            updiag[0+column]--;
            downdiag[0-column+num]--;
        }
        fout << counter << endl;
        return 0;
    }
    short half_num = num/2;
    for(short column = 0; column < half_num; column++){
        DFS(0,column);
        //Unmark the placement
        col_mark[column]--;
        updiag[0+column]--;
        downdiag[0-column+num]--;
    }
    if(num%2 == 0)
        fout << counter * 2 << endl;
    else{
        int cur_counter = counter;
        counter = 0;
        DFS(0,half_num);
        cur_counter = cur_counter*2 + counter;
        fout << cur_counter<<endl;
    }
//    t = clock() - t;
//    cout<<"Comsume time: "<<  ((float)t)/CLOCKS_PER_SEC <<endl;
    return 0;
}
