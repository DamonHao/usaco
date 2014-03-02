/*
既然要装下尽可能多的物品，那么就应该先选入小的物品。所以，先把物品按照重量递增排序。那么：
1）如果前k物品不能装入背包，那么即使把其中一个物品P换成k+1~R中的一个物品Q，
   由于Q的重量大于P，因此也绝对不可能成功装入背包。
2）如果前k个物品可以装入背包，那么前k-1个物品也一定能装入背包。
3）如果前k个物品不能装入背包，那么前k+1个物品也一定不能装入背包。
这样，一个最值问题就转化成了判定性问题，只要枚举出可行的最大k值就可以了。
从2、3两个结论中还可以得知可行性与k的关系是“单调”的，因此，可以使用二分查找优化枚举(貌似不二分也可以通过所有数据)。
为方便起见，记所有背包的容量和为boardsum，前k个物品重量和为railsum[k]。

1）重量大于最大背包容量的物品可以直接删去，容量小于最小物品重量的背包也可以直接删去。（这不算剪枝，应该是预处理）
2）如果可以把前k个物品全部装入，那么浪费掉的容量waste一定是boardsum-railsum[k]。当一个背包的剩余容量小于物品重量的最小值，
   即不能装入任何物品时，把剩余的容量加到current_waste中，一旦current_waste > waste,就说明这种情况一定不能找到解，应该回溯（比较强大）。
3）如果存在两个物品p1,p2的重量相等，因此可以把他们看作是一样的，所以可以直接固定p2的顺序，把它放在p1后面（非常强大）。
4）如果railsum[k]>boardsum,那么这k个物品一定不能放入背包。
5）改变搜索顺序也可以加快速度，由于放入较大的物品是比较难的，因此dfs的时候可以从大的物品开始。
  （这点很容易被忘记，但有些时候改变顺序的确很有效）

第1个剪枝是本人自己想到的。2，3，4都是从NOCOW和google上搜到的，真的很难想到，尤其是第三个。
refer to Jimmy's Thoughts
*/
/*
Executing...
   Test 1: TEST OK [0.000 secs, 3520 KB]
   Test 2: TEST OK [0.000 secs, 3520 KB]
   Test 3: TEST OK [0.011 secs, 3520 KB]
   Test 4: TEST OK [0.011 secs, 3520 KB]
   Test 5: TEST OK [0.011 secs, 3520 KB]
   Test 6: TEST OK [0.022 secs, 3520 KB]
   Test 7: TEST OK [0.000 secs, 3520 KB]
   Test 8: TEST OK [0.011 secs, 3520 KB]
   Test 9: TEST OK [0.011 secs, 3520 KB]
   Test 10: TEST OK [0.000 secs, 3520 KB]
   Test 11: TEST OK [0.000 secs, 3520 KB]
   Test 12: TEST OK [0.000 secs, 3520 KB]
All tests OK.
Your program ('fence8') produced all correct answers!  This is your
submission #3 for this problem.  Congratulations!
*/
/*
ID: haolink1
PROG: fence8
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <algorithm>    // std::sort
using namespace std;

const int MAX_RAIL = 1024;

int N,R;
int rail[MAX_RAIL];
int board[50];
int boardsum;
int railsum[MAX_RAIL];
int cut_rail_from[MAX_RAIL];
int max_waste,cur_waste; 
ifstream fin("fence8.in");
ofstream cout("fence8.out");
bool SmallFirst(int a, int b){return a < b;}
bool BigFirst(int a, int b){return a > b;}

void init(){
    fin >> N;
    for(int i = 0; i < N; i++){
        fin >> board[i];
        boardsum += board[i];
    }
    fin >> R;
    for(int i = 0; i < R; i++){
        fin >> rail[i];
    }
    sort(rail,rail+R,SmallFirst);
    sort(board,board+N,BigFirst);
    //ignore impossible boards and rails
    while(rail[R - 1] > board[0] && R > 0)    R --;
    while(N > 0 && board[N - 1] < rail[0])    N --;
    if(R == 0 || N == 0){   //The case there is no solution;
        cout << 0 << endl;
        exit(0);//Note to exit, not return;
    }
    railsum[0] = rail[0];
    for(int i = 1;i < R;i ++){
        railsum[i] = railsum[i - 1] + rail[i];
    }
}

bool DFS_Check(int index){
    if(cur_waste > max_waste) return 0;
    if(index < 0) return 1;
    int start = 0;
    if(rail[index] == rail[index+1]) //Note the case index == 1022; so we allocate 1024 for rail; 
        start = cut_rail_from[index+1];
    for(int i = start; i < N; i++){
        if(board[i] >= rail[index]){
            board[i] -= rail[index];
            cut_rail_from[index] = i;
            if(board[i] < rail[0]) cur_waste += board[i];
            int remain = DFS_Check(index-1);
            //restore;
            if(board[i] < rail[0]) cur_waste -= board[i];
            cut_rail_from[index] = -1;
            board[i] += rail[index];
            // We only need one of the solution to put remain rails;
            // Once we find it, return true right away;
            if(remain) return 1; 
        }
    }
    return 0;
}

void BinarySearch(){
    for(int i = 0; i < R; i++) cut_rail_from[i] = -1;
    int low = 0,hight = R - 1;
    for(; hight >= 0 && boardsum < railsum[hight]; hight--);
    while(low < hight){
        //Note here we plus 1 because when low +1 == hight, we want to check mid == hight; 
        int mid = (low + hight + 1)/2; 
        max_waste = boardsum - railsum[mid];
        if(DFS_Check(mid)) low = mid;
        else hight = mid - 1;
    }
    cout << low + 1 << endl;
}

int main(){
    init();
    BinarySearch();
    return 0;
}
