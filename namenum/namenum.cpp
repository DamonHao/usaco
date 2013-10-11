/*
ID: haolink1
PROG: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

char map_table[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
     'P','R','S','T','U','V','W','X','Y'};

bool ChekcMatch(char num, char cur_char){
    //ASCII '2' = 50
    for(char i = 0; i < 3 ; i++){
        if(map_table[(num-50)*3+i] == cur_char)
            return true;
    }
    return false;
}

bool CheckValid(string& brand_num, string& name,char& match_state){
//once the first character of two string have match, the next time they dismatch,
//then the following name is invalid because the name'character sort in ascending order
    if(ChekcMatch(brand_num[0],name[0]))// the first character begin to match
        match_state = 1;
    else{ 
        if(match_state == 1)//the first character dismatch after they have matched;
            match_state = 2;
        return false;
    }
    if(brand_num.length()!= name.length())
        return false;
    for(unsigned int i = 1; i < brand_num.length();i++){
        if(!ChekcMatch(brand_num[i],name[i]))
            return false;
    }
    return true;
}

int main(){
    ifstream fin("namenum.in");
    string brand_num;
    getline(fin,brand_num);
    ifstream dicts("dict.txt");
    string name;
    getline(dicts,name);    
    vector<string> valid_names;
    char match_state = 0;
    while(name.compare("") != 0){
        if(CheckValid(brand_num,name,match_state))
            valid_names.push_back(name);  
        if(match_state == 2)
            break;
        getline(dicts,name);
    }
    ofstream fout("namenum.out");
    if(valid_names.size() == 0)
        fout<<"NONE"<<endl;
    else{
        for(unsigned int i = 0; i < valid_names.size();i++)
            fout<<valid_names[i]<<endl;
    }
    return 0;
}
