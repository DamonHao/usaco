/*
ID: haolink1
PROG: ariprog
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // std::sort
//#include <time.h> 
using namespace std;
typedef unsigned int u_int;

class Solution{
public:
    int begin_;
    int diff_;
    Solution(int begin,int diff):
        begin_(begin),diff_(diff){}
};

bool CompareDiff(Solution first, Solution second){
    if(first.diff_ < second.diff_)
        return true;
    else if(first.diff_ == second.diff_ && first.begin_ < second.begin_)
        return true;
    else return false;
}

int main(){
//    time_t timer_begin;
//    time(&timer_begin);
//    ofstream fout_log("logfile");
    ifstream fin("ariprog.in");
    int prog_len = 0;
    int upper_bound = 0;
    fin >> prog_len;
    fin >> upper_bound;
    vector<int> squares;
    for(int i = 0; i <= upper_bound; i++)
        squares.push_back(i*i);
    vector<int> bisquares;
    //comsume more memory to trade for speed, very important
    bool bisquares_array[125001]={false};
    for(int i = 0; i <= upper_bound; i++){
        for(int j = 0; j <= upper_bound; j++){
           bisquares_array[squares[i]+squares[j]] = true; 
        }    
    }
    //collect the sorted bisquare 
    for(u_int i = 0; i < 125001; i++){
        if(bisquares_array[i]== true)
            bisquares.push_back(i);
    }
//    for(u_int i = 0; i < bisquares.size(); i++)
//        fout_log<<bisquares[i]<<" ";
//    cout<<endl;
//    cout<<bisquares.size()<<endl;
    vector<Solution> solutions;
    int bisquares_len = bisquares.size();
    int max_value = bisquares[bisquares_len-1];
    for(int i = 0; i < bisquares_len-2; i++){
        int begin = bisquares[i]; 
        for(int diff = 1; begin+diff*(prog_len-1) <= max_value; diff++){
            int target_len = 1;
            for(int k = i+1; k < bisquares_len; k++){
                //fout_log<<bisquares[k]<<" "; 
                //u_int temp = bisquares[k];
                if((begin + diff * target_len) < bisquares[k]){
                    break;
                }else if((begin + diff * target_len) == bisquares[k]){
                    target_len++;
                    if(target_len == prog_len){
                        solutions.push_back(Solution(begin,diff)); 
                        break;
                    }
                } 
            }
        }
    }
    sort(solutions.begin(),solutions.end(),CompareDiff);
    ofstream fout("ariprog.out");
    int size = solutions.size();
//    cout<<size<<endl;
    if(size == 0){
        fout<<"NONE"<<endl;
        return 0;
    }
    for(int i = 0; i < size; i++){
        fout<<solutions[i].begin_<<" "<<solutions[i].diff_<<endl;
    }
//    time_t timer_end;
//    time(&timer_end);
//    cout<<endl<<"Comsume time: "<<timer_end -timer_begin<<endl;
    return 0;
}
