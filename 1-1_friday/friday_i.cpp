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
int isleap(int year){
    return year%4==0 && (year%100 != 0 || year%400 == 0);
}

/* return length of month m in year y */
int MonthLen(int year, int month,int* month_table){

    if(month == 1)    /* february */
        return month_table[month]+isleap(year);
    else
        return month_table[month];
}

int main()
{
    ifstream fin("friday.in");
    string period_str;
    getline(fin,period_str);
    int period = atoi(period_str.c_str());
    //start form Saturday
    int category_couter[] = {0,0,0,0,0,0,0};
    int month_table[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //January 13, 1900 was a Saturday,so day_of_week = 0
    int day_of_week = 0;
    for(int current_year = 1900;current_year<1900+period;current_year++){
         for(int month=0;month<12;month++){
            category_couter[day_of_week]++;
            day_of_week=(day_of_week+MonthLen(current_year,month,month_table))%7;
         }
    }
        ofstream fout("friday.out");
    int i=0;
    for(;i<6;i++){
        fout<<category_couter[i]<<" ";
    }
    fout<<category_couter[i]<<endl;
    return 0;
}
