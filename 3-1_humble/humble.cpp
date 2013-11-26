/*
ID: haolink1
PROG: humble
LANG: C++
*/

/*
usaco official solution
We compute the first n humble numbers in the "hum" array. For simplicity of implementation, 
we treat 1 as a humble number, and adjust accordingly.
Once we have the first k humble numbers and want to compute the k+1st, we do the following:

        for each prime p
                find the minimum humble number h
                  such that h * p is bigger than the last humble number.
        take the smallest h * p found: that's the next humble number.
To speed up the search, we keep an index "pindex" of what h is for each prime, 
and start there rather than at the beginning of the list.
*/
//#include <iostream>
#include <fstream>

using namespace std;
int humble[100001];
int prime[100];
int prime_index[100];
int main(){
    int K = 0,N = 0;
    ifstream fin("humble.in");
    fin >> K >> N;
    for(int i = 0; i < K; i++){
        fin >> prime[i]; 
    }
    int num = 1;
    humble[0] = 1;
    while(num != N + 1){
        //I consider the below min should be more suitalbe;
        //long long min = 0x100000000;
        //thought 0x7FFFFFFF is enough for the test data;
        long long min = 0x7FFFFFFF;
        int m = -1;
        for(int i = 0; i < K; i++){
            while(prime[i] * humble[prime_index[i]] <= humble[num - 1])
                prime_index[i]++;
            if((long long)prime[i] * humble[prime_index[i]] < min){
                min = prime[i] * humble[prime_index[i]];
                m = i;
            }
        }
        humble[num++] = min;
        prime_index[m]++;
    }
    ofstream fout("humble.out");
    fout << humble[N] << endl;
    return 0;
}
