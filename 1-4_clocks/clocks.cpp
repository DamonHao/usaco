//Considering this problem, we should know that:
//1 the order of the move is meaningless;
//2 any move perform 4 times is meaningless;
//So the total case is 4^9 = 262144, the amount is ok
//It's said that this problem can also be solved by BFS and DFS,
//but I can't find the proper answer

/*
ID: haolink1
PROG: clocks
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

short ModuloAdd(short value){
    value=(value+3)%12;
    if(value == 0)
        return 12;
    else return value;
}

void Move(short* clocks,short move){
//    for(short i = 0; i < 9; i++){
//        clocks_new[i] = clocks[i];
//    }
    switch(move){
        case 1:
           clocks[0]=ModuloAdd(clocks[0]); 
           clocks[1]=ModuloAdd(clocks[1]); 
           clocks[3]=ModuloAdd(clocks[3]); 
           clocks[4]=ModuloAdd(clocks[4]);
           break;
        case 2:
           clocks[0]=ModuloAdd(clocks[0]); 
           clocks[1]=ModuloAdd(clocks[1]); 
           clocks[2]=ModuloAdd(clocks[2]); 
           break;
        case 3:
           clocks[1]=ModuloAdd(clocks[1]); 
           clocks[2]=ModuloAdd(clocks[2]); 
           clocks[4]=ModuloAdd(clocks[4]); 
           clocks[5]=ModuloAdd(clocks[5]); 
           break; 
        case 4:
           clocks[0]=ModuloAdd(clocks[0]); 
           clocks[3]=ModuloAdd(clocks[3]); 
           clocks[6]=ModuloAdd(clocks[6]); 
           break;
        case 5:
           clocks[1]=ModuloAdd(clocks[1]); 
           clocks[3]=ModuloAdd(clocks[3]); 
           clocks[4]=ModuloAdd(clocks[4]); 
           clocks[5]=ModuloAdd(clocks[5]); 
           clocks[7]=ModuloAdd(clocks[7]); 
           break;
        case 6:
           clocks[2]=ModuloAdd(clocks[2]); 
           clocks[5]=ModuloAdd(clocks[5]); 
           clocks[8]=ModuloAdd(clocks[8]); 
           break;
        case 7:
           clocks[3]=ModuloAdd(clocks[3]); 
           clocks[4]=ModuloAdd(clocks[4]); 
           clocks[6]=ModuloAdd(clocks[6]); 
           clocks[7]=ModuloAdd(clocks[7]); 
           break;
        case 8:
           clocks[6]=ModuloAdd(clocks[6]); 
           clocks[7]=ModuloAdd(clocks[7]); 
           clocks[8]=ModuloAdd(clocks[8]); 
           break;
        case 9:
           clocks[4]=ModuloAdd(clocks[4]); 
           clocks[5]=ModuloAdd(clocks[5]); 
           clocks[7]=ModuloAdd(clocks[7]); 
           clocks[8]=ModuloAdd(clocks[8]); 
           break;
    }
}

void TotalMove(short* clocks, short* move_times){
    for(short i = 0; i < 9; i++){
        for(short j = 0; j < move_times[i]; j++)
            Move(clocks,i+1);
    }   
}

bool CheckMatch(short* clocks){
    for(short i =0; i < 9; i++){
        if(clocks[i] != 12)
            return false;
    }
    return true;
}

void CopyArray(short* source, short* destination, short len){
    for(short i = 0; i < len; i++){
       destination[i] = source[i]; 
    }
}


int main(){
    ifstream fin("clocks.in");
    short* original = new short[9];
    for(int i = 0; i < 9; i++)
        fin >> original[i];
    //Note to initialize each array,in case strange output;
    //the value of times[0] means the times we operate move 1, and so on; 
    short times[9]={0,0,0,0,0,0,0,0,0};
    short solution[9]={0,0,0,0,0,0,0,0,0};
    short min_step = 28;// the max step is 27 
    short temp_clocks[9]={0,0,0,0,0,0,0,0,0};
    //Begin loop from the hight weight of times, because we chose the solution which 
    //gives the lowest number when the moves are concatenated, eg 5 2 4 6 < 9 3 1 1
    for(times[8] = 0 ; times[8] < 4; times[8]++){
        for(times[7] = 0 ; times[7] < 4; times[7]++){
            for(times[6] = 0 ; times[6] < 4; times[6]++){
                for(times[5] = 0 ; times[5] < 4; times[5]++){
                    for(times[4] = 0 ; times[4] < 4; times[4]++){
                        for(times[3] = 0 ; times[3] < 4; times[3]++){
                            for(times[2] = 0 ; times[2] < 4; times[2]++){
                                for(times[1] = 0 ; times[1] < 4; times[1]++){
                                    for(times[0] = 0 ; times[0] < 4; times[0]++){
                                        short cur_step = times[0]+times[1]+times[2]+times[3]+times[4]+times[5]+times[6]+times[7]+times[8];
                                        //we can ignore the case cur_step == min_step, because the low weight of times increase first;
                                        if(cur_step  < min_step){
                                            CopyArray(original,temp_clocks,9);
                                            TotalMove(temp_clocks,times); 
                                            if(CheckMatch(temp_clocks)){
                                                CopyArray(times,solution,9);
                                                min_step = cur_step;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } 
                }
            }
        } 
    }
    //cout << min_step <<endl;
    vector<short> final_solution;
    for(short i = 0; i < 9; i++){
        for(short j = 0; j < solution[i]; j++) 
            final_solution.push_back(i+1);
    }
    ofstream fout("clocks.out");
    short len = final_solution.size();
    for(short i = 0; i < len-1; i++)
        fout << final_solution[i]<<" ";
    if(len >= 1)
        fout<<final_solution[final_solution.size()-1] <<endl;
}
