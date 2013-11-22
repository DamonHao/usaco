/*
ID: haolink1
PROG: ttwo
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

bool obstacle[10][10];
bool farmer_record[10][10][4];
bool cows_record[10][10][4];

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

//Note the algoritm won't work;
//The main idea is if both the farmer and cows finish a cycle walk of their own and if they 
//didn't meet yet, then they won't never meet;
//But it may happen that after  farmer walk n cycles and cows walk m cycles then they meet;
//That is ,each cycle thye move close a bit;
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
    bool farmer_finish_a_round = 0;
    bool cows_finish_a_round = 0;
    while(1){
        farmer.Move();
        cows.Move();
        minutes++;
        if(farmer == cows){
            fout<< minutes <<endl;
            return 0;
        }
        if(farmer_record[farmer.x][farmer.y][farmer.direct] == 1){ 
            farmer_finish_a_round = 1;
            cout<<"F "<<minutes<<endl;
        }
        else 
            farmer_record[farmer.x][farmer.y][farmer.direct] = 1;
        if(cows_record[cows.x][cows.y][cows.direct] == 1){
            cows_finish_a_round = 1;
            cout<<"C "<<minutes<<endl;
        }
        else
            cows_record[cows.x][cows.y][cows.direct] = 1;
        if(farmer_finish_a_round == 1 && cows_finish_a_round == 1){
            cout<<minutes<<endl;
            fout<< 0 <<endl;
            return 0;
        }
    }
    return 0;
}
