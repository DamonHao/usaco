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

bool CheckValid(bool* bisquares,int begin,int diff,int prog_len){
    for(int i = 1; i < prog_len; i++){
        //This is the most direct way to check the existence of the arithmetic progression
        if(bisquares[begin + diff*i] == false)
            return false;
    } 
    return true;
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
    //Note: comsume more memory to trade for speed, very important
    const int  max_size = 125001;
    bool bisquares_array[max_size]={false};
    for(int i = 0; i <= upper_bound; i++){
        for(int j = 0; j <= upper_bound; j++){
           bisquares_array[squares[i]+squares[j]] = true; 
        }    
    }
    vector<Solution> solutions;
    int max_bisquare = upper_bound*upper_bound*2;
    //The enumerate all case, we need triple loop, so we must choose the 
    //most costless way by reducing unnecessary computation and indexing; 
    //Enumerate first term
    for(int i=0; i < max_size; i++){
        if(bisquares_array[i] == true){
            //Enumerate tolerance
            //Use i+diff*(prog_len-1) <= max_bisquare to reduce unnecessary computation
            for(int diff = 1; i+diff*(prog_len-1) <= max_bisquare; diff++){
                if(CheckValid(bisquares_array,i,diff,prog_len)) 
                    solutions.push_back(Solution(i,diff)); 
            }
        }        
    }
    sort(solutions.begin(),solutions.end(),CompareDiff);
    ofstream fout("ariprog.out");
    int size = solutions.size();
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
