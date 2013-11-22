/*
ID: haolink1
PROG: ttwo
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

bool obstacle[10][10];
//Record all the state of farmer and cows in one minutes; 
//record[farmer.x][farmer.y][cows.x][cows.y][farmer.direct][cows.direct]
bool record[10][10][10][10][4][4];

class Object {
public:
    short x;
    short y;
    short direct; // north 0; east 1; south 2; west 3;
    Object(){
        x = 0; y = 0; direct = 0;
    }
    bool operator==(Object& obj1){
        if(x == obj1.x && y == obj1.y){
            return true;
        }
        return false;
    }
    void Rotate(){
        direct = (direct+1)%4;
    }
    void Move(){
        switch(direct){
            case 0:
                if(x-1 >= 0 && obstacle[x-1][y] == 0) x--;
                else Rotate();
                break;
            case 1:
                if(y+1 < 10 && obstacle[x][y+1] == 0) y++;
                else Rotate();
                break;
            case 2:
                if(x+1 < 10 && obstacle[x+1][y] == 0) x++;
                else Rotate();
                break;
            case 3:
                if(y-1 >= 0 && obstacle[x][y-1] == 0) y--;
                else Rotate();
                break;
        }
    }
};

//Main idea:
//brute force
//We use record[farmer.x][farmer.y][cows.x][cows.y][farmer.direct][cows.direct] to record 
//all the state of farmer and cows in one minutes, if they come back to one state and didn't 
//meet yet, then they will never meet;
//The key point of this problem is how to decide in which case the farmer and cows will never meet;
int main(){
    ifstream fin("ttwo.in");
    char symbol;
    Object farmer,cows;
    for(short i = 0; i < 10; i++){
        for(short j = 0; j < 10; j++){
            fin >> symbol;
            if(symbol == '*')
                obstacle[i][j] = 1;
            else if(symbol == 'F'){
                //cout <<'F'<<i+1<<j+1<<endl;
                farmer.x = i;
                farmer.y = j;
            }else if(symbol == 'C'){
                //cout<<'C'<< i+1 << j+1<<endl;
                cows.x = i;
                cows.y = j;
            }
        }
    } 
    int  minutes = 0;
    ofstream fout("ttwo.out");
    while(1){
        farmer.Move();
        cows.Move();
        minutes++;
        if(farmer == cows){
            fout<< minutes <<endl;
            return 0;
        }
        if(record[farmer.x][farmer.y][cows.x][cows.y][farmer.direct][cows.direct] == 1){
            fout<<0<<endl;
            return 0;
        }
        else
            record[farmer.x][farmer.y][cows.x][cows.y][farmer.direct][cows.direct] = 1;
    }
    return 0;
}
