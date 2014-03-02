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

int gcd(int a,int b)
{
    if(a<b) swap(a,b);

    int tmp;

    while(b!=0){
        tmp = a;
        a = b;
        b = tmp%b;
    }

    return a;
}

void solve()
{

    fin>>box_num;
    for(int i=0;i<box_num;++i)
        fin>>boxs[i];

    sort(&boxs[0],&boxs[box_num]);
    
    int t = boxs[0];

    for(int i=1;i<box_num;++i){
        t = gcd(t,boxs[i]);
    }

    if(t!=1){
        cout<<0<<endl;
        return;
    }

    memset(ok,0,sizeof(ok));

    int last = 0;
    ok[0] = true;
    int i=0;

    while(true){
        if(ok[i%256]){
            ok[i%256] = 0;
            if(i-last>=boxs[0]){
                cout<<last<<endl;
                return;
            }
            for(int x=0;x<box_num;++x){
                ok[(i+boxs[x])%256] = true;
            }
        }else{
            last = i;
        }
        ++i;
    }
}

int main(int argc,char *argv[])
{
    solve(); 
    return 0;
}

