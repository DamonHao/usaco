/*
这题有些难。虽然知道是动态规划题，但是不知道要开多大的数组，后来看analysis用一个256大小的数组循环使用，方法很巧妙。
先将box进行排序。
如果box里面的数的最大公约数不为1的话，那么所有组成的数，只可能是这个公约数的倍数，因此没有上限，输出为0.
用last记录最小的“不能组成的数”。这样当last之后有boxs[0]个连续数都可以组成的话，那么所有的数都可以组成。
last+1...last+box[0]可以组成的话，那么每个数都加一个box[0],那么新一轮的box[0]个数也可以组成，以此类推。
refer to 止于自娱;
*/

/*
Executing...
   Test 1: TEST OK [0.000 secs, 3504 KB]
   Test 2: TEST OK [0.000 secs, 3504 KB]
   Test 3: TEST OK [0.000 secs, 3504 KB]
   Test 4: TEST OK [0.000 secs, 3504 KB]
   Test 5: TEST OK [0.011 secs, 3504 KB]
   Test 6: TEST OK [0.000 secs, 3504 KB]
   Test 7: TEST OK [0.000 secs, 3504 KB]
All tests OK.
YOUR PROGRAM ('nuggets') WORKED FIRST TIME!
*/

/*
ID: haolink1
PROG: nuggets
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <algorithm>    // std::sort
#include <cstring>

using namespace std;
ifstream fin("nuggets.in");
ofstream cout("nuggets.out");
int box_num;
int boxs[10];
bool ok[256];

int Gcd(int a,int b){
    do{
     int r = a % b;
     a = b;
     b = r;
    }while(b!=0);
    return a;
}
bool Compare(int i,int j) { return (i<j); }
int main(){
    fin >> box_num;
    for(int i = 0; i < box_num; i++){
        fin >> boxs[i];
    }
    sort(boxs,boxs+box_num-1,Compare);
    int t = boxs[0];
    for(int i = 1; i < box_num; i++){
        t = Gcd(t,boxs[i]);
    }
    if(t != 1){
        cout << 0 << endl;
        return 0;
    }
    ok[0] = 1;
    int last = 0;int cur = 0;
    while(cur <= 2000000000){
        if(ok[cur%256]){
            ok[cur%256] = 0;
            if(cur - last >= boxs[0]){
                cout << last << endl;
                return 0;
            }
            for(int i = 0; i < box_num; i++){
                ok[(cur+boxs[i])%256] = 1;
            }
        }else{
            last = cur;
        }
        cur++;
    }
    //Note the case when cur > 2000000000 didn't show in test data;
    cout << last << endl;
    return 0;
}
