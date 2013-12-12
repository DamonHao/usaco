/*
可以算是一道数学题吧。如果知道皮克定理就好写多了。
皮克定理说明了其面积S和内部格点数目a、边上格点数目b的关系：S = a + b/2 - 1。 
根据三角形面积公式求出S。如果知道了b，那么三角形内部格点数目a也就求出来了。 
可以证明，一条直线((0,0),(n,m))上的格点数等于n与m的最大公约数+1。 
即b=gcd(n,m)+1. gcd(n,m)为n与m的最大公约数。 代入皮克公式，即可求出a的值。
refer to byvoid;
*/
/*
Executing...
   Test 1: TEST OK [0.011 secs, 3500 KB]
   Test 2: TEST OK [0.000 secs, 3500 KB]
   Test 3: TEST OK [0.000 secs, 3500 KB]
   Test 4: TEST OK [0.000 secs, 3500 KB]
   Test 5: TEST OK [0.000 secs, 3500 KB]
   Test 6: TEST OK [0.000 secs, 3500 KB]
   Test 7: TEST OK [0.000 secs, 3500 KB]
   Test 8: TEST OK [0.011 secs, 3500 KB]
   Test 9: TEST OK [0.000 secs, 3500 KB]
   Test 10: TEST OK [0.000 secs, 3500 KB]
   Test 11: TEST OK [0.000 secs, 3500 KB]
   Test 12: TEST OK [0.000 secs, 3500 KB]

All tests OK.
*/

/*
ID: haolink1
PROG: fence9
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */

using namespace std;
ifstream fin("fence9.in");
ofstream cout("fence9.out");

int Gcd(int a, int b){
    int tmp;
    while(b > 0){
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int Compute(int n,int m,int p){
    double S,b;
    S = p * m / 2.0;
    int w1 = Gcd(m,n);
    int w2 = Gcd(m,abs(n-p));
    b = w1 + w2 + p;
    return S - b/2.0 + 1;
}

int main(){
    int n = 0,m = 0,p = 0;
    fin >> n >> m >> p;
    cout << Compute(n,m,p) << endl; 
    return 0;
}
