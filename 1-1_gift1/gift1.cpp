/*
ID: haolink1
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <assert.h>
using namespace std;
//compute the member position for earnings array
unsigned short MemberPosition(char** name_array,unsigned short group_num,
                              char* name){
    unsigned short i=0;
    for(;i<group_num;i++){
        if(strcmp(name_array[i],name)==0)
            return i;
    }
    cout<<"MemberPosition error"<<endl;
    assert(i<group_num);
    return 0;
}
//note the length string
void ExtractSting(char* giving_info,unsigned short giving_info_len,
                   char* giving_money, unsigned short giving_money_len,
                   char* receiver_num, unsigned short receiver_num_len ){
    unsigned short i=0;
    for(;i<giving_info_len;i++){
        if(giving_info[i] == ' ' && i!=0){
            strncpy(giving_money,giving_info,giving_money_len-1);
            /* null character manually added */
            giving_money[giving_money_len-1]='\0';
            strncpy(receiver_num,giving_info+i+1,receiver_num_len-1);
            receiver_num[receiver_num_len-1]='\0';
            return;
        }
    }
}

int main(){
    ifstream fin("gift1.in");
    char group_number_char[3];
    fin.getline(group_number_char,3);
    unsigned short group_num = atoi(group_number_char);
    if(group_num < 2 || group_num > 10)
        return 0;
    //read name
    char** name_array=new char* [group_num];
    int* earnings = new int[group_num];
    for(unsigned short i=0;i<group_num;i++){
        name_array[i] = new char[14];
        fin.getline(name_array[i],14);
        earnings[i] = 0;
    }
    //handle the each member transaction
    for(unsigned short i=0;i<group_num;i++){
        char* giver = new char[14];
        fin.getline(giver,14);
        char giving_info[10];
        fin.getline(giving_info,10);
        char give_money_str[6];
        char receiver_num_str[4];
        ExtractSting(giving_info,10,give_money_str,5,receiver_num_str,3);
        unsigned short give_money = atoi(give_money_str);
        unsigned short receiver_num = atoi(receiver_num_str);
        if(receiver_num==0)
         continue;
        //update earnings
        unsigned short received_money = give_money/receiver_num;

        for(unsigned short i=0;i<receiver_num;i++){
            char receiver[14];
            fin.getline(receiver,14);
            //update receivers' earnings
            earnings[MemberPosition(name_array,group_num,receiver)]+=received_money;
        }
        //update giver's earnings
        earnings[MemberPosition(name_array,group_num,giver)]-=received_money*receiver_num;
    }
    ofstream fout ("gift1.out");
    for(unsigned short i=0;i<group_num;i++){
        fout<<name_array[i]<<" "<<earnings[i]<<endl;
        delete name_array[i];
    }
    delete[] earnings;
    return 0;
}
