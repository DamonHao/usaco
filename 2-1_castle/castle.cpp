/*
ID: haolink1
PROG: castle
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

const short MAX = 50;
//Record the visited info and then the room the module belong to;
short module_info[MAX][MAX];
//
short room_size[MAX*MAX] = {0};
//Record the wall info.
bool no_walls[MAX][MAX][4];
short room_num = 0;
short room_size_counter = 0;
void DFS(short row,short column);
class Solution{
public:
    short row_;
    short column_;
    short max_size;
    char direction;
    Solution(){
        row_ = -1;
        column_ = -1;
        max_size = 0;
        direction = ' ';
    }
};
//Main Idea 
//We use DFS to find the number of room and module_info[MAX][MAX]
//to record the visited info and then the room the module belong to;
int main(){
    ifstream fin("castle.in");
    short column = 0;
    short row = 0;
    fin >> column;
    fin >> row;
    short walls_info = 0;
    for(short i = 0; i < row; i++){
        for(short j = 0; j < column; j++){
            fin >> walls_info;
            //Note:We should take care the map between the num and the wall
            //and look the in binary form which is useful to retrieve the wall info.
            //Eg: 1,2,4,8 their binary form is 0001,0010,0100,1000, we can use & operator 
            //to retrieve the wall info.
            if( !(walls_info & 1))//no west wall
                no_walls[i][j][0] = true;
            if(!(walls_info & 2))//no north wall
                no_walls[i][j][1] = true;
            if(!(walls_info & 4))//no east wall
                no_walls[i][j][2] = true;
            if(!(walls_info & 8))//no south wall
                no_walls[i][j][3] = true;

//            if(walls_info%2 == 0) //To west
//                no_walls[i][j][0] = true;
//            if(walls_info!=2 && walls_info !=3 && walls_info !=6 && walls_info!=7 && walls_info!=10 &&
//                walls_info!=11 && walls_info!=14 && walls_info!=15)//To north
//                no_walls[i][j][1] = true;
//            if(walls_info!=4 && walls_info!=5 && walls_info!=6 && walls_info!=7 && walls_info < 12)//To east
//                no_walls[i][j][2] = true;
//            if(walls_info < 8)//To south
//                no_walls[i][j][3] = true;
            
            //Initialization. -1 mean the module haven't been visited;
            module_info[i][j] = -1;
        }
    }
    for(short i = 0; i < row; i++){
        for(short j = 0; j < column; j++){
            DFS(i,j);
            if(room_size_counter > 0){
                room_size[room_num] = room_size_counter;
                room_num++;
                room_size_counter = 0;
            }
        }
    }
    ofstream fout("castle.out");
    //Room num
    fout << room_num <<endl;
    //Max size room
    short max_size = 0;
    for(short i = 0; i < room_num; i++){
        if(room_size[i] > max_size) 
            max_size = room_size[i];
    }
    fout << max_size <<endl;
    //find the optimal wall to remove 
    Solution solution;
    //First find the most north, then the most east, we traverse all modules one by one.
    //This is the easiest way to implement to find the optimal wall to remove.
    for(short j = 0; j < column; j++){
        for(short i = row-1; i >= 0; i--){
            short temp_size = 0;
            if(i > 0 && no_walls[i][j][1] == false && module_info[i][j] != module_info[i-1][j]){//Check North
                temp_size =room_size[module_info[i][j]] + room_size[module_info[i-1][j]]; 
                if(temp_size > solution.max_size){
                    solution.max_size = temp_size;
                    solution.row_ = i;
                    solution.column_ = j;
                    solution.direction = 'N';
                }
            }
            if(j < column-1 && no_walls[i][j][2] == false && module_info[i][j] != module_info[i][j+1]){//Check East
                temp_size = room_size[module_info[i][j]] + room_size[module_info[i][j+1]];  
                if(temp_size > solution.max_size){
                    solution.max_size = temp_size;
                    solution.row_ = i;
                    solution.column_ = j;
                    solution.direction = 'E';
                }
            }
        }
    }

    fout << solution.max_size <<endl;
    fout << solution.row_+1 <<" "<< solution.column_+1<<" "<<solution.direction<<endl;
    return 0;
}

void DFS(short row,short column){
    if(module_info[row][column] != -1)
        return;
    //Keep the room which the module belong to;
    module_info[row][column] = room_num;
    room_size_counter++;
    if(no_walls[row][column][0] == true)
       DFS(row,column-1); 
    if(no_walls[row][column][1] == true)
        DFS(row-1,column);
    if(no_walls[row][column][2] == true)
        DFS(row,column+1);
    if(no_walls[row][column][3] == true)
        DFS(row+1,column);
}
