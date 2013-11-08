/*
ID: haolink1
PROG: holstein
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const short max_vitamins = 25;
const short max_feeds = 15;
short feeds_vitamins[max_feeds][max_vitamins];

void CopyArray(short* first,short* second,short len);
bool AllNoPositive(short* element,short len);

//Main Idear
//The key point of this problem is "Cows can be fed at most one scoop of any feed type"
//Then the max conbination of feeds is 2^15 = 32768,because for each feed type
//we can choose to add it or not.So the brute force is acceptable. 
int main(){
    ifstream fin("holstein.in");
    short vitamins_num = 0;
    fin >> vitamins_num; 
    short* target_vitamins = new short[vitamins_num];
    for(short i = 0; i < vitamins_num; i++){
        fin >> target_vitamins[i];
    }
    short feeds_num = 0;
    fin >> feeds_num;
    for(short i = 0; i < feeds_num; i++){
        for(short j = 0; j < vitamins_num; j++){
            fin >> feeds_vitamins[i][j];
        }
    }
    int  total_combination = 1;
    for(short i = 0; i < feeds_num; i++){
       total_combination *= 2; 
    }
    short* temp_vitamins = new short[vitamins_num];
    short min_type = feeds_num+1;
    vector<short> feeds;
    //Note the variable i's type can't be short,because if i want to go out the its loop,
    //its value must reach 32768
    for(int i = 1; i < total_combination; i++){
        short checker = 1;
        CopyArray(target_vitamins,temp_vitamins,vitamins_num);
        for(short j = 0;j < feeds_num; j++){
            //Note this is a good way to express whether we choose one feed type
            //by operator &
            if(i&(checker<<j)){
                for(short k = 0; k < vitamins_num; k++){
                   temp_vitamins[k] -= feeds_vitamins[j][k]; 
                }
                if(AllNoPositive(temp_vitamins,vitamins_num)){
                    short total_type = 0;
                    for(short m = 0; m < feeds_num; m++){
                        if(i & (checker << m)){
                            total_type++;
                        }
                    }
                    if(total_type < min_type){
                        min_type = total_type;
                        feeds.clear();
                        for(short m = 0; m < feeds_num; m++){
                            if(i & (checker << m)){
                                feeds.push_back(m);
                            }
                        }
                    } 
                }
            }
        } 
    } 
    ofstream fout("holstein.out");
    fout<<min_type<<" ";
    short feeds_size = feeds.size();
    for(short m = 0; m < feeds_size-1; m++){
        fout<<feeds[m]+1<<" ";
    }
    if(feeds_size > 0)
        fout<<feeds[feeds_size - 1]+1<<endl;
    delete[] target_vitamins;
    return 0;
}

void CopyArray(short* first,short* second,short len){
    for(short i = 0; i < len; i++){
        second[i] = first[i];
    }
}

bool AllNoPositive(short* element,short len){
    for(short i = 0; i < len; i++){
        if(element[i] > 0 ){
            return false;
        }
    }
    return true;
}
