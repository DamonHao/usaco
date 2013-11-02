/*
ID: haolink1
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

unsigned int StringValue(string name){
    unsigned int value=1;
    for(unsigned int i=0;i < name.length();i++){
       //A==65
       value *=((unsigned int)(name[i])-64);
    }
    return value%47;
}

int main()
{
    string comet_name;
    string group_name;
    ifstream fin("ride.in");
    getline(fin,comet_name);
    getline(fin,group_name);
    ofstream fout ("ride.out");
    if(StringValue(comet_name)==StringValue(group_name)){
        fout<<"GO"<<endl;
    }else{
        fout<<"STAY"<<endl;
    }
    return 0;
}
