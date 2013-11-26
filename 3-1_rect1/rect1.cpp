/*
ID: haolink1
PROG: rect1
LANG: C++
*/

//#include <iostream>
#include <fstream>

using namespace std;

class Rect{
public:
    int llx,lly,urx,ury,color;
};
const int color_num = 2500;
Rect rect[1001];
int square[color_num+1];
int N = 0;
int cur_color = 0;
void Compute(int llx,int lly,int urx,int ury,int posit){
    do posit++;
    while(posit <= N && (urx <= rect[posit].llx || llx >= rect[posit].urx ||
          ury <= rect[posit].lly || lly >= rect[posit].ury));
    if(posit > N){
       square[cur_color] += (urx - llx)*(ury - lly); 
    }else{
        if(llx < rect[posit].llx){
            Compute(llx,lly,rect[posit].llx,ury,posit);
            llx = rect[posit].llx;
        }
        if(urx > rect[posit].urx){
            Compute(rect[posit].urx,lly,urx,ury,posit);
            urx = rect[posit].urx;
        }
        if(lly < rect[posit].lly){
            Compute(llx,lly,urx,rect[posit].lly,posit);
            //lly = rect[posit].lly;
            //Note: no need to update lly, because it won't be use in
            //the following function; So take care if you change its order;
        }
        if(ury > rect[posit].ury){
            Compute(llx,rect[posit].ury,urx,ury,posit);
            //ury = rect[posit].ury;
        }
    }
}
/*
思路大概是这样的，首先读入所有的矩形。我们可以发现最后覆盖的矩形不会被其他矩形覆盖，所以可以考虑从后向前覆盖。
对于每个矩形，我们把它和有可能覆盖在它上面的矩形(就是出现在当前矩形后面的矩形)比较，
如果两个矩形有重叠部分就把重叠部分去掉，把当前矩形分成几个小矩形递归进行分割。
直到当前矩形与后面的矩形全部没有公共部分，累加矩形的面积。
Refer to byvoid;
*/
int main(){
    int A = 0, B  = 0;
    ifstream fin("rect1.in");
    ofstream fout("rect1.out");
    fin >> A >> B >> N;
    for(int i = 1; i <= N; i++){
        fin >> rect[i].llx >> rect[i].lly >> rect[i].urx >> rect[i].ury >> rect[i].color;
    }
//    for(int i = 1; i <= N; i++){
//        cout << rect[i].llx << endl;
//    }
    rect[0].llx = 0;rect[0].lly = 0; rect[0].urx = A; rect[0].ury = B; rect[0].color = 1;
    for(int i = N; i >= 0; i--){
        cur_color = rect[i].color;
        Compute(rect[i].llx,rect[i].lly,rect[i].urx,rect[i].ury,i); 
    }
    for(int i = 1; i <= color_num; i++){
        if(square[i] != 0)
            fout<< i << " " << square[i] << endl;
    }
    return 0;
}
