/*
ID: haolink1
PROG: friday
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
int main()
{
    ifstream fin("friday.in");
    string period_str;
    getline(fin,period_str);
    int period = atoi(period_str.c_str());
    int current_year = 1900;
    unsigned short category_couter[] = {0,0,0,0,0,0,0};
    //value 0 means Monday
    unsigned short month_1th_daty_category = 0;
    for(int i=0;i<period;i++){
        for(int month=1;month<13;month++){
            category_couter[(month_1th_daty_category+12)%7]++;
            //update the value of month_1th_daty_category for next month
            if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
                month_1th_daty_category=(month_1th_daty_category+31)%7;
            }else if(month==4||month==6||month==9||month==11){
                month_1th_daty_category=(month_1th_daty_category+30)%7;
            }else{
                //leap year
                if(current_year%400==0||(current_year%100!=0 && current_year%4==0)){
                month_1th_daty_category=(month_1th_daty_category+29)%7;
                }else{// not leap year
                month_1th_daty_category=(month_1th_daty_category+28)%7;
                }
            }
        }
        current_year++;
    }
    ofstream fout("friday.out");
    int i=0;
    for(;i<6;i++){
        fout<<category_couter[(i+5)%7]<<" ";
    }
    fout<<category_couter[(i+5)%7]<<endl;
    return 0;
}
