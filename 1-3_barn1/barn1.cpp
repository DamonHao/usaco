/*
ID: haolink1
PROG: barn1
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <list>
using namespace std;

bool CompareInterval(int free_interval_1, int free_interval_2){
    if(free_interval_1 <= free_interval_2)
        return true;
    else
        return false;
}

// by increasement order, T(n)=O(n^2)
void InsertionSort(int* array, int length) {
    for (int j = 1; j < length; j++) {
            int key = array[j];
            int i = j - 1;
            while (i >= 0 && array[i] > key) {
                    array[i + 1] = array[i];
                    i--;
            }
            array[i + 1] = key;
    }
}
int main(){
    ifstream fin("barn1.in");
    int max_boards = 0;
    int total_stalls = 0;
    int occupied_stalls = 0;
    fin >> max_boards;
    fin >> total_stalls;
    fin >> occupied_stalls;
    //count the number of serial occupied-stall interval 
    int serial_interval_num = 0;
    list<int> free_intervals;
    int cur_occupied = 0;
    int prev_occupied = 0;
    int* occupied_stall_position = new int[occupied_stalls]; 
    for(int i = 0; i < occupied_stalls; i++){
        fin >> occupied_stall_position[i];
    }
    //sort the position in ascending order
    InsertionSort(occupied_stall_position,occupied_stalls); 
    for(int i = 0; i < occupied_stalls; i++){
        cur_occupied = occupied_stall_position[i];
        //note the way to count the serial interval number, while cur_occupied is exception;
        if(cur_occupied == 1 || prev_occupied+1 != cur_occupied){
            serial_interval_num++;
            if(prev_occupied != 0)//the free interval made of the free stall before the first occupied stall is meaningless
                free_intervals.push_back(cur_occupied - prev_occupied -1); 
        }
        prev_occupied = cur_occupied;
    }
    int stalls_blocked = occupied_stalls;
    if(serial_interval_num > max_boards){
        free_intervals.sort(CompareInterval);
        for(int i = 0; i < serial_interval_num - max_boards; i++){
            stalls_blocked += free_intervals.front();
            free_intervals.pop_front();
        }
    }
    ofstream fout("barn1.out");
    fout << stalls_blocked <<endl;
    delete[] occupied_stall_position;
    return 0;
}
