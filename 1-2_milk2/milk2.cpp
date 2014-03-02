/*
ID: haolink1
PROG: milk2
LANG: C++
*/
//#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;
typedef unsigned int u_int;

class TimeInterval{
public:
    int begin_;
    int end_;
    TimeInterval(int begin, int end):begin_(begin),end_(end){}
    TimeInterval(const TimeInterval& source){
        begin_ = source.begin_;
        end_ = source.end_;
    }
    ~TimeInterval(){}
};
bool CompareBeginTime(const TimeInterval& first, const TimeInterval& second){
    if(first.begin_ < second.begin_)
        return true;
    else return false;
}
int main(){
    ifstream fin ("milk2.in");
    u_int farmers_num;
    fin >> farmers_num;
    list<TimeInterval> milk_times;
    int begin = 0;
    int end = 0; 
    for(u_int i = 0; i < farmers_num; i++){
        fin >> begin;
        fin >> end;
        //converge time intervals
        for(list<TimeInterval>::iterator it = milk_times.begin(); it != milk_times.end();){
            if(end < (*it).begin_ || begin > (*it).end_){ //two time intervals are disjoint
                it++;
                continue;
            }
            end = end > (*it).end_?end:(*it).end_;
            begin = begin < (*it).begin_?begin:(*it).begin_;
            list<TimeInterval>::iterator it_temp = it;
            it++;
            milk_times.erase(it_temp);
        }
        milk_times.push_back(TimeInterval(begin,end));
    }
    //sort disjoint time intervals by begin time in increasing order
    milk_times.sort(CompareBeginTime);
    int max_continous = 0;
    int max_idle = 0;
    for(list<TimeInterval>::iterator it = milk_times.begin(); it != milk_times.end(); ++it){
        max_continous = max_continous > (it->end_ - it->begin_)?max_continous:(it->end_ - it->begin_);
        list<TimeInterval>::iterator it_temp = it;
        if((++it)!=milk_times.end()){
            int idle_time = it_temp->begin_ - it->end_;
            if(idle_time < 0)
                idle_time = it->begin_ - it_temp->end_;
             max_idle = max_idle > idle_time?max_idle:idle_time;
        }     
        it = it_temp;
    }
//        cout<<max_continous<<endl;
//        cout<<max_idle<<endl;
    ofstream fout("milk2.out");
    fout<<max_continous<<" "<<max_idle<<endl;  
    return 0;
}
