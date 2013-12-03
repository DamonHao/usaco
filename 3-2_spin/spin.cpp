/*
Main idea
The key point of this problem is you should note the fact that at 360 second, 
all 5 wheels will go back to his initial state; see 360 * speed is a full period;
So only the time [0,360) is meanningful, and we can mimic the this process by
enumeration;

*/

/*
ID: haolink1
PROG: spin
LANG: C++
*/

//#include <iostream>
#include <fstream>

using namespace std;

class Wheel{
public:
    int speed_,w_num_;
    int w_start_[5];
    int w_end_[5];
};

Wheel wheel[5];
ifstream fin("spin.in");
ofstream cout("spin.out");
bool Check(){
    for(int angle = 0; angle < 360; angle++){
        short counter = 0;
        for(int i = 0; i < 5; i++){
            bool flag = false;
            for(int j = 0; j < wheel[i].w_num_; j++){//Note the condition w_end_[j] < w_start_[j] 
                if((angle >= wheel[i].w_start_[j] && angle <= wheel[i].w_end_[j] && wheel[i].w_end_[j] >= wheel[i].w_start_[j]) ||
                      ((angle <= wheel[i].w_end_[j] || angle >= wheel[i].w_start_[j]) && wheel[i].w_end_[j] < wheel[i].w_start_[j])){
                    flag = true; 
                } 
                if(flag){
                    counter++;
                    break;
                }
            }        
        }
        if(counter == 5){
            return true;
        }
    }
    return false;
}

void Print(int time){
    if(time == -1)
        cout << "none" << endl;
    else cout << time << endl;
}

int main(){
    int extent = 0;
    for(int i = 0; i < 5; i++){
        fin >> wheel[i].speed_;
        fin >> wheel[i].w_num_;
        for(int j = 0; j < wheel[i].w_num_; j++){
            fin >> wheel[i].w_start_[j];
            fin >> extent;
            wheel[i].w_end_[j] = wheel[i].w_start_[j] + extent;
            if(wheel[i].w_end_[j] >= 360)//note, the end angle may bigger than 360; 
                wheel[i].w_end_[j] -= 360;
        }
    }
    
    for(int t = 0; t < 360; t++){
        if(Check()){
            Print(t);
            return 0;
        }
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < wheel[i].w_num_; j++){
                wheel[i].w_start_[j]+=wheel[i].speed_;
                if(wheel[i].w_start_[j] >= 360)
                    wheel[i].w_start_[j] -= 360;
                wheel[i].w_end_[j]+=wheel[i].speed_;
                if(wheel[i].w_end_[j] >= 360)
                    wheel[i].w_end_[j] -= 360;
            } 
        }
    }
    Print(-1);
    return 0;
}
