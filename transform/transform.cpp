/*
ID: haolink1
PROG: transform
LANG: C++
*/
#include<iostream>
#include <fstream>
using namespace std;
typedef unsigned int u_int;

bool Is90(char** first_pattern,char** second_pattern,u_int row_num){
    for(u_int i = 0; i < row_num; i++){
        for(u_int j = 0; j < row_num; j++){
            if(first_pattern[i][j] != second_pattern[j][row_num-1-i])
                return false;
        }
    }
    return true;
}

bool Is180(char** first_pattern, char** second_pattern, u_int row_num){ 
    for(u_int i = 0; i < row_num; i++){
        for(u_int j = 0; j < row_num; j++){
            if(first_pattern[i][j] != second_pattern[row_num-1-i][row_num-1-j])
                return false;
        }
    }
    return true;
}

bool Is270(char** first_pattern, char** second_pattern, u_int row_num){ 
    for(u_int i = 0; i < row_num; i++){
        for(u_int j = 0; j < row_num; j++){
            if(first_pattern[i][j] != second_pattern[row_num-1-j][i])
                return false;
        }
    }
    return true;
}

bool Reflection(char** first_pattern, char** second_pattern, u_int row_num){
    for(u_int i = 0; i < row_num; i++){
        for(u_int j = 0; j < row_num; j++){
            if(first_pattern[i][j] != second_pattern[i][row_num-1-j])
                return false;
        }
    }
    return true; 
}

void Reflect(char** source_pattern, char** target_pattern, u_int row_num){
    for(u_int i = 0; i < row_num; i++){
        for(u_int j = 0; j < row_num; j++){
            target_pattern[i][row_num-1-j] = source_pattern[i][j];
        }
    } 
}

bool NoChange(char** first_pattern, char** second_pattern, u_int row_num){
    for(u_int i = 0; i < row_num; i++){
        for(u_int j = 0; j < row_num; j++){
            if(first_pattern[i][j] != second_pattern[i][j])
                return false;
        }
    }
    return true;  
}

int main(){
    ifstream fin ("transform.in");
    u_int row_num = 0;
    fin>>row_num;
    char** first_pattern = new char*[row_num]; 
    for(u_int i = 0; i < row_num; i++)
        first_pattern[i] = new char[row_num]; 
    for(u_int i = 0; i < row_num; i++)
        fin>>first_pattern[i];

    char** second_pattern = new char*[row_num]; 
    for(u_int i = 0; i < row_num; i++)
        second_pattern[i] = new char[row_num]; 
    for(u_int i = 0; i < row_num; i++)
        fin>>second_pattern[i];
    //judge pattern
    u_int pattern = 0;
    if(Is90(first_pattern,second_pattern,row_num))
        pattern = 1;
    else if(Is180(first_pattern,second_pattern,row_num))
        pattern = 2;
    else if(Is270(first_pattern,second_pattern,row_num))
        pattern = 3;
    else if(Reflection(first_pattern,second_pattern,row_num))
        pattern = 4;
    else{
        char** temp_pattern = new char*[row_num]; 
        for(u_int i = 0; i < row_num; i++)
            temp_pattern[i] = new char[row_num]; 
        Reflect(first_pattern,temp_pattern,row_num);
        if(Is90(temp_pattern,second_pattern,row_num)||Is180(temp_pattern,second_pattern,row_num)
        ||Is270(temp_pattern,second_pattern,row_num))
            pattern = 5;
        else if(NoChange(first_pattern,second_pattern,row_num))
            pattern = 6;
        else
            pattern = 7;
        for(u_int i = 0; i < row_num; i++){
            delete[] temp_pattern[i];
        }
    }
    ofstream fout("transform.out");
    fout<<pattern<<endl;
    //cout<<pattern<<endl;
    //cout<<first_pattern[2]<<endl;
    //cout<<second_pattern[2]<<endl;
    for(u_int i = 0; i < row_num; i++){
        delete[] first_pattern[i];
        delete[] second_pattern[i];
    }
     
    return 0;
}

