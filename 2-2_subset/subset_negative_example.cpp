/*
ID: haolink1
PROG: subset
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

short subset[20] = {0};
short subset_len = 0;
int subset_counter = 0;
short max_num = 0;
short half_sum = 0;

void DFS(short begin,short depth);
bool CheckSum();

//Main Idea
//Enumerate by recursion.But it will TLE even I prune a lot of branches.
//The reason is n! increase so fast.
int main(){
    ifstream fin("subset.in");
    fin >> max_num;
    short sum = max_num*(max_num+1)/2;
    ofstream fout("subset.out");
    if(sum % 2 != 0){
        fout<<0<<endl;
        return 0;
    }
    half_sum = sum/2;
    int target_set_num = 0;
    for(subset_len = 1; subset_len <= max_num/2; subset_len++){
        //Note you can't just enumerate begin upto max_num/2;
        for(short begin = 1; begin <= max_num; begin++){
            DFS(begin,1); 
        }
        if(subset_len % 2 != 0){
            target_set_num += subset_counter;
        }else{
            subset_counter /= 2;
            target_set_num += subset_counter;
        }
        //reset
        subset_counter = 0;
    }
    fout<<target_set_num<<endl;
    return 0;
}

//depth start from 1;
void DFS(short begin,short depth){ 
    subset[depth-1] = begin;
    if(depth >= subset_len){
        if(CheckSum())
            subset_counter++;
        return;
    }
    for(short i = begin+1; i <= max_num; i++){
        //Note: prune some branch
        short remain_depth = subset_len - (depth+1);
        //Check whether the leftover number of set is enough for remain depth 
        //after we choose value i;
        if((max_num - i) >= remain_depth){
            //Check whether the max sum of subet is big enough to reach half sum
            //after we choose value i;
            short max_rise = 0;
            for(short j = 0; j < remain_depth; j++){
                max_rise += (max_num-j); 
            }
            short cur_sum = 0;
            for(short j = 0; j < depth; j++){
                cur_sum += subset[j];
            }
            cur_sum += i;
            if(cur_sum + max_rise >= half_sum)
                DFS(i,depth+1); 
        }
    } 
}



bool CheckSum(){
    short cur_sum = 0;
    for(short i = 0; i < subset_len;i++){
        cur_sum += subset[i];
    }
    /*
    if(cur_sum == half_sum){
        for(short i = 0; i < subset_len;i++){
            cout<<subset[i]<<" ";
        }
        cout<<endl;
    }
    */
    return (cur_sum == half_sum);
}
