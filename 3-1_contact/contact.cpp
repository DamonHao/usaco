
/*
 经典的位运算解题，边读入边计算。 设置极限掩码为limit=(1<<(B))-1; //2的B此次方-1 
每读入一个二进制数0或1，令unsigned int数字串str=((str<<1)+c) & limit; 
然后扫描str，从末尾向前扫描i=(A到B)位，把所得的数字串t最高位添加1，以区别有前导0的串，例如001和01，添加后变为1001和101

mask=(1<<i)-1;
mask2=mask+1;
t=(S & mask) | mask2;
用哈希表记录t的频率 hash[t]++;

最后再排序按格式输出即可，一定要小心输出格式。
-- refer to byVoid
*/

/*
ID: haolink1
PROG: contact
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // std::sort
using namespace std;
typedef unsigned int u_int;

class Pattern{
public:
    u_int freq_;
    u_int value_;
    Pattern(int freq,u_int value):
        freq_(freq),value_(value){}
};

int A = 0,B = 0,N = 0;
const int MAX = (1<<13);
u_int hash[MAX];
void Vote(unsigned int str, unsigned int str_len){
    for(int i = A; i <= B && i <= str_len; i++){
       u_int mask = (1 << i) -1;
       u_int mask2 = mask + 1;
       u_int t = (str & mask) | mask2;
       hash[t]++;
    } 
}
bool Compare(Pattern p1,Pattern p2 ){
    if(p1.freq_ > p2.freq_){
        return true; 
    }else if(p1.freq_ == p2.freq_ && p1.value_ < p2.value_){//Shorter string have less value,eg 101(len = 2) and 1001(len =3)
        return true;
    }else return false;
}

void ChangeFormat(u_int source,char target[]){
    int bit_num = A;
    for(;bit_num <= B; bit_num++){
        if(!(source >> (bit_num+1)))
            break;
    }
    for(int i = bit_num -1; i >= 0; i--){
        if(source & (1 <<(bit_num - i - 1))){
            target[i] = '1';
        }else{
            target[i] = '0';
        }
    }
    target[bit_num] = '\0';
}

int main(){
    ifstream fin("contact.in");
    ofstream cout("contact.out");
    fin >> A >> B >> N;
    char val;
    unsigned int limit = (1 << B)-1;
    unsigned int str, str_len = 0;
    while(fin >> val){
        val -= 48;
        str = ((str << 1) + val) & limit;//The digit highter then B will be kicked off by "limit";
        str_len ++;
        Vote(str,str_len);
    } 
    vector<Pattern> patterns;
    for(int i = 0; i < MAX; i++){
        if(hash[i] != 0){
            patterns.push_back(Pattern(hash[i],i));
        }
    }
    sort(patterns.begin(),patterns.end(),Compare);
    u_int cur_freq = -1 ; 
    int counter = 0;
    int per_line = 1;
    int len = patterns.size();
    for(int i = 0; i < len; i++){
        char target[13];
        if(patterns[i].freq_ < cur_freq){
            counter++;
            per_line = 1;
            if(counter > N){
                break;
            }
            cur_freq = patterns[i].freq_;
            cout << patterns[i].freq_ << endl;
            ChangeFormat(patterns[i].value_,target);
            cout << target;
        }else{
            ChangeFormat(patterns[i].value_,target);
            cout << target;
        }
        //Note condition 1 should put first because  per_line == 0 can be caught by condition 2;
        if((i+1 == len) || (patterns[i+1].freq_ < cur_freq) || (per_line == 0))//condition 1
            cout << endl;
        else if(i+1 < len && patterns[i+1].freq_ == cur_freq)//condition 2
            cout <<" ";
        ++per_line;
        per_line = per_line % 6;
    }
    return 0;
}
