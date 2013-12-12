/*
Main idea:
一道动态规划题，但观察数据规模，穷举就行了。 
穷举每首歌是否选取所有的组合可能(2^20种)，算出每种情况所有光盘上一共能存的歌曲数目，保留最大值即可。
对于穷举每首歌是否选取所有的组合可能，我采用了位运算的高效方法
limit=(1 << N)-1;
for (i=0;i<=limit;i++)
然后i对应的每种状况计算能装进光盘中的最大的歌曲数目即可。
refer to byvoid;
*/

/*
Executing...
   Test 1: TEST OK [0.000 secs, 3500 KB]
   Test 2: TEST OK [0.000 secs, 3500 KB]
   Test 3: TEST OK [0.000 secs, 3500 KB]
   Test 4: TEST OK [0.000 secs, 3500 KB]
   Test 5: TEST OK [0.000 secs, 3500 KB]
   Test 6: TEST OK [0.022 secs, 3500 KB]
   Test 7: TEST OK [0.248 secs, 3500 KB]
   Test 8: TEST OK [0.324 secs, 3500 KB]
   Test 9: TEST OK [0.097 secs, 3500 KB]
   Test 10: TEST OK [0.000 secs, 3500 KB]
   Test 11: TEST OK [0.313 secs, 3500 KB]
   Test 12: TEST OK [0.313 secs, 3500 KB]
All tests OK.
*/
/*
ID: haolink1
PROG: rockers
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 20;
int len[MAX];

int main(){
    int N = 0,T = 0,M = 0;
    ifstream fin("rockers.in");
    ofstream cout("rockers.out");
    fin >> N >> T >> M;
    for(int i = 0; i < N; i++){
        fin >> len[i];
    }
    int limit = (1 << N) -1;
    int use[MAX];
    int max_num = 0;
    for(int i = 1; i <= limit; i++){
        memset(use,0,sizeof(use)); 
        int st = 0, cur_num = 0; 
        for(int j = 0; j < N; j++){
            bool cur = (1 << j) & i;
            if(cur){
                for(int k = st; k < M; k++){
                    if(use[k] + len[j] <= T){
                        use[k] += len[j];
                        cur_num++;
                        break;
                    }
                    st++;
                }
            }
        }
        if(cur_num > max_num)
            max_num = cur_num;
    }
    cout << max_num << endl;
}
