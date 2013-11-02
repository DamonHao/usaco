/*
ID: haolink1
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream fin ("beads.in");
    unsigned int num;
    fin >> num;
    string beads;
    fin >> beads;
    if(beads.length() != num){
        cout<<"error"<<endl;
        return 0;
    }
    int max_num = 0;
    //Brute force !
    for(unsigned int i = 0;i < num;i++){
        int cur_num = 0;
        int diff = 0;
        //just choose a arbitrary char different from 'w' 'b' and 'r';
        char sample = 'n';
        //we transform the bidirectional collection in to unidirectional,
        //and when the beads'color difference occur twice, the collection stop;
        for(unsigned int j = 0;j < num;j++){
            if(beads[(i+j)%num]!='w' && beads[(i+j)%num]!=sample){
                sample = beads[(i+j)%num];
                diff++;
                if(diff<=2)
                    cur_num++;
                else break;
            }else
                cur_num++;
        }
        max_num=(cur_num>max_num)?cur_num:max_num;
    }
    ofstream fout ("beads.out");
    fout<<max_num<<endl;
    return 0;
}
