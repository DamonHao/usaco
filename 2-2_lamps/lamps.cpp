/*
ID: haolink1
PROG: lamps
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>
using namespace std;

short turn_on_index[100];
short turn_off_index[100];
bool lamp_state[100] = {true};  
bool lamp_final_state[16][100];


void ChangeButtonState(short button_state[],short lamp_num);
bool CheckValid(short turn_on_num, short turn_off_num);
bool CompareBinaryValue(bool* first,bool* second);

//Main idea:
//Reading the problem condition, we can know that
//1: the order we press the button mean nothing for the final lamp state;
//2: when the button is pressed even times, it mean nothing for the final lamp state;
//With the above tow conclusion, we can find that the number of final state is 16=2^4 at most;
int main(){
    ifstream fin("lamps.in");
    short lamp_num = 0;
    short counter = 0;
    fin >> lamp_num >> counter;
    short temp = 0;
    fin >> temp;
    short turn_on_num = 0;
    while(temp != -1){
        turn_on_index[turn_on_num++] = temp;
        fin >> temp;
    }
    fin >> temp;
    short turn_off_num = 0;
    while(temp != -1){
        turn_off_index[turn_off_num++] = temp;
        fin >> temp;
    }
    short button_state[4];
    short ans_counter = 0;
    for(button_state[0] = 0; button_state[0] < 2; button_state[0]++){
        for(button_state[1] = 0; button_state[1] < 2; button_state[1]++){
            for(button_state[2] = 0; button_state[2] < 2; button_state[2]++){
                for(button_state[3] = 0; button_state[3] < 2; button_state[3]++){
                    //Reset
                    for(short i = 0; i < lamp_num; i++){
                        lamp_state[i] = true;
                    }
                    short press_num = 0;
                    for(short i = 0; i < 4; i++){
                        press_num += button_state[i];
                    }
                    //Note: take care the relationship between press_num and the counter;
                    if((press_num <= counter)&&(press_num % 2 == counter % 2)){
                        ChangeButtonState(button_state,lamp_num);
                        if(CheckValid(turn_on_num,turn_off_num)){
                            for(short i = 0; i < lamp_num; i++){
                                //cout<<lamp_state[i];
                                lamp_final_state[ans_counter][i] = lamp_state[i];    
                            }
                            ans_counter++;
                            //cout<<endl;
                        }         
                    } 
                }
            }
        }
    }
    ofstream fout("lamps.out");
    if(ans_counter == 0){
        fout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    vector<bool*> my_vector(lamp_final_state,lamp_final_state+ans_counter);
    sort(my_vector.begin(),my_vector.end(),CompareBinaryValue);
    //Note the lamp_final_state[0...16] isn't RandomAccessIterator,because that are not stored adjacently in memory;
    //sort((bool**)lamp_final_state,(bool**)(lamp_final_state + ans_counter -1),CompareBinaryValue);
    for(short i = 0; i < ans_counter; i++){
        for(short j = 0; j < lamp_num; j++){
            fout<< my_vector[i][j];
        }
        fout<<endl;
    }
    return 0;
}

void ChangeButtonState(short button_state[],short lamp_num){
    if(button_state[0] == 1){
        for(short i = 0; i < lamp_num; i++){
            lamp_state[i] = !lamp_state[i];
        }
    }
    if(button_state[1] == 1){
        for(short i = 0; i < lamp_num; i+=2){
            lamp_state[i] = !lamp_state[i];
        }
    }
    if(button_state[2] == 1){
        for(short i = 1; i < lamp_num; i+=2){
            lamp_state[i] = !lamp_state[i];
        }
    }
    if(button_state[3] == 1){
        for(short i = 0; i < lamp_num; i+=3){
            lamp_state[i] = !lamp_state[i];
        }
    }
} 

bool CheckValid(short turn_on_num, short turn_off_num){
    for(short i = 0; i < turn_on_num; i++){
        if(lamp_state[turn_on_index[i]-1] == false)
            return false;
    }
    for(short i = 0; i < turn_off_num; i++){
        if(lamp_state[turn_off_index[i]-1] == true)
            return false;
    }
    return true;
}

bool CompareBinaryValue(bool* first,bool* second){
    short counter= 0;
    while(first[counter] == second[counter])
        counter++;
    if(second[counter])
        return true;
    else return false;
}
