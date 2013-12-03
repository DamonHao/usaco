/*
这道题类似于八数码难题，基本思想是宽搜，使用Hash判重。如果使用一般的八维数组空间可以达到8^8=16777216，
会超过USACO的16MB空间限制。所以我们应该对状态进行散列存储，观察发现每位的数字不能重复，
存在空间冗余。我们可以对于每个状态建立一个映射，采用康托展开算法。(参见Nocow) 定义cantor(s)为s串大大小顺序。
可样将哈希容量缩减到8!=40320。

另外发现，对于魔板当前状态可以由一个8位的8进制数来表示，即无符号32位长整型 unsigned long 表示。 
对于魔板的变换可以转化为对一个数字的位运算。这样可以大大提高程序效率。 
Refer to byvoid. 

本题中我自己使用 int 来表示魔板的当前的状态。因为8位8进制数不会使 int 变为负数，使得移位操作符合本题要求。
*/

/*
ID: haolink1
PROG: msquare
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <queue> 
#include <string>
using namespace std;
const int MAX = 40320;
bool hash[MAX];
long fac[8]={1,1,2,6,24,120,720,5040};
ifstream fin("msquare.in");
ofstream cout("msquare.out");
int target_state = 0;
int node_state[MAX][3]; // Keep nodes's distance, parent and transform way;

int Cantor(int cur_state){
    int x=0,k=0,p=0;
    bool is_visited[8] = {false};
    for(int i = 8; i >= 2; i--){
        k = cur_state >> 3*(i-1);
        cur_state -= k << 3*(i-1);
        is_visited[k] = true;
        p = k;
        for(int j = 0; j <= k-1; j++){
            if(is_visited[j])
                p--;
        }
        x += fac[i-1]*p;
    }
    return x;
}

void Init(){
    int val = 0;
    for(int i = 0; i < 8; i++){
        fin >> val;
        val--;
        target_state += (val << 3*(7-i));
    }
}

int Transform(int cur_state, int trans){
    int final_state = 0, k = 0;
    switch(trans){
        case 0:
            for(int i = 0; i < 4; i++){
                k = ((7 << 3*i) & cur_state) << 3*(7-i*2);
                final_state += k;
                k = ((7 << 3*(7-i)) & cur_state) >> 3*(7-i*2);
                final_state += k;
            }
            break;
        case 1:
            k = (cur_state & 07000) >>(3*3);
            k += (cur_state & 0777) <<3;
            final_state = (cur_state & 070000) << (3*3);
            final_state += (cur_state & 077700000) >> 3;
            final_state += k;
            break;
        case 2:
            final_state = cur_state & 070077007;
            k += (cur_state & 070) <<(5*3);
            k += (cur_state & 0700) >> 3;
            k += (cur_state & 0700000) >>(3*3);
            k += (cur_state & 07000000) >> 3;
            final_state += k;
            break;
    }
    return final_state;
}

void BFS(){
    int intial_state = 0;
    for(int i = 0; i < 8; i++){
        intial_state += (i << 3*(7-i));
    }
    hash[0] = true;
    node_state[0][0] = 0;
    if(intial_state == target_state)
        return;
    queue<int> state_queue;
    state_queue.push(intial_state);
    bool flag = true;
    while((!state_queue.empty()) && flag == true){
        int cur_state = state_queue.front();
        int cur_cantor = Cantor(cur_state);
        state_queue.pop();
        for(int j = 0; j <3; j++){
            int next_state = Transform(cur_state,j);
            int next_cantor = Cantor(next_state);
            if(!hash[next_cantor]){
                hash[next_cantor] = 1;
                state_queue.push(next_state);
                node_state[next_cantor][0] = node_state[cur_cantor][0]+1;//distance 
                node_state[next_cantor][1] = cur_cantor;//parent
                node_state[next_cantor][2] = j;//tranform way;
                if(next_state == target_state){
                    flag = false;
                    break;
                }
            }
        }
    }
}

void Print(){
    int cur_cantor = Cantor(target_state);
    cout << node_state[cur_cantor][0]<<endl;
    string str;
    while(cur_cantor != 0){
        str += 'A'+node_state[cur_cantor][2];
        cur_cantor = node_state[cur_cantor][1];
    }
//    cout << str << endl;
    int len = str.length();
    if(len == 0){
        cout << endl;
        return;
    }
    int counter = 0; 
    for(int i = len-1; i >= 0; i--){
        counter++;
        cout << str[i];
        if(counter == 60){
            cout << endl;
            counter = 0;
        }
    }
    if(counter != 0)
        cout << endl;
}

int main(){
    
    Init();
    //cout << oct << target_state << endl;
    //cout << oct << Transform(target_state,2) << endl;
    BFS();
    Print();
    return 0;
}
