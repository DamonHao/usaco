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

//void AddUniqueVaule(vector<u_int>& bisquares,u_int value){
//   for(u_int i = 0; i < bisquares.size(); i++){
//       if(bisquares[i] == value)
//           return;
//   } 
//   bisquares.push_back(value);
//}
//
//bool CompareValue(u_int first, u_int second){
//    if(first < second)
//        return true;
//    else return false;
//}

class Solution{
public:
    u_int begin_;
    u_int diff_;
    Solution(u_int begin,u_int diff):
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
    time_t timer_begin;
    time(&timer_begin);
    ofstream fout_log("logfile");
    ifstream fin("ariprog.in");
    int prog_len = 0;
    int upper_bound = 0;
    fin >> prog_len;
    fin >> upper_bound;
    vector<u_int> squares;
    for(int i = 0; i <= upper_bound; i++)
        squares.push_back(i*i);
    vector<u_int> bisquares;
//    for(int i = 0; i <= upper_bound; i++){
//        for(int j = 0; j <= upper_bound; j++){
//            AddUniqueVaule(bisquares,squares[i]+squares[j]); 
//        }    
//    }
//    sort(bisquares.begin(),bisquares.end(),CompareValue); 
//    for(int i = 0; i < bisquares.size(); i++){
//        cout<<bisquares[i]<<" "; 
//    }
//    cout<<endl;
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
    cout<<bisquares.size()<<endl;
    vector<Solution> solutions;
    u_int begin = 0; u_int diff  = 0;
    int bisquares_len = bisquares.size();
    for(int i = 0; i < bisquares_len-2; i++){
        begin = bisquares[i]; 
        for(int j = i+1; j < bisquares_len-1; j++){
            diff = bisquares[j] - bisquares[i];
            int target_len = 2;
            for(int k = j+1; k < bisquares_len; k++){
                //fout_log<<bisquares[k]<<" "; 
                u_int temp = bisquares[k];
                if((begin + diff * target_len) < bisquares[k]){
//                    cout<<"test"<<endl;
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
    if(size == 0){
        fout<<"NONE"<<endl;
        return 0;
    }
    for(int i = 0; i < size; i++){
        fout<<solutions[i].begin_<<" "<<solutions[i].diff_<<endl;
    }
    time_t timer_end;
    time(&timer_end);
    cout<<endl<<"Comsume time: "<<timer_end -timer_begin<<endl;
    return 0;
}
