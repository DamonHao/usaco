/*
Main idea:
1.判断多边形是否合法
任两条边都不相交即合法，注意这里的相交是严格相交，顶点相交不算相交。
2.二分法判断当前线段 seg_a 是否可见
假设观察点为 eye，seg_a 的两个端点分别为st 和 end。判断视线（eye，st）和（eye，end）是否
与其他线段（即 fence）相交。
如果都不相交，则seg_a 可见。
如果两视线均与某一 fence 相交，则seg_a不可见。
如果所有线段都只与其中一视线相交，则将seg_a 二分，设 mid 为其中点，二分后为（st，mid）和 （mid，end）
在判断这两线段是否可见，如果其中之一可见，则seg_a可见。最后，在二分后的线段足够小的情况下还未可见，则
seg_a 不可见。
//PS:我发现所有的测试点的多边形都是合法的
*/
/*
Executing...
   Test 1: TEST OK [0.000 secs, 3508 KB]
   Test 2: TEST OK [0.000 secs, 3508 KB]
   Test 3: TEST OK [0.000 secs, 3508 KB]
   Test 4: TEST OK [0.011 secs, 3508 KB]
   Test 5: TEST OK [0.011 secs, 3508 KB]
   Test 6: TEST OK [0.076 secs, 3508 KB]
   Test 7: TEST OK [0.043 secs, 3508 KB]
   Test 8: TEST OK [0.011 secs, 3508 KB]
   Test 9: TEST OK [0.065 secs, 3508 KB]
   Test 10: TEST OK [0.043 secs, 3508 KB]
   Test 11: TEST OK [0.000 secs, 3508 KB]
   Test 12: TEST OK [0.000 secs, 3508 KB]
All tests OK.
*/
/*
ID: haolink1
PROG: fence4
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <cmath>
#define EPS 1e-6

using namespace std;
int N = 0;
ifstream fin("fence4.in");
ofstream cout("fence4.out");
class Point{
public: 
    double x_,y_;
    Point(double x = 0,double y = 0):x_(x),y_(y){}
    Point(const Point & p):x_(p.x_),y_(p.y_){}
    void operator=(const Point& p){
        x_ = p.x_;
        y_ = p.y_;
    }    
};
class Seg{
public: 
    Point st_,end_;
};

Point eye;
Seg segs[200];
bool segs_seen[200];

double CrossProduct(const Point& p1,const Point& p2){
    return p1.x_*p2.y_ - p2.x_*p1.y_;
}

Point P2Vect(Point a,Point b){
   b.x_ = b.x_-a.x_;
   b.y_ = b.y_-a.y_;
   return b;
}

bool DiffSide(Seg& s1,Seg& s2){
    Point v1 = P2Vect(s1.st_,s1.end_);
    double t1 = CrossProduct(v1,P2Vect(s1.end_,s2.st_));
    double t2 = CrossProduct(v1,P2Vect(s1.end_,s2.end_));
    if(t1==0 && t2 == 0) return 0;//This case is s1 and s2 is on a line but they don't corss; 
    if(t1*t2 <= 0) return 1;
    else return 0;
}

bool SegCross(Seg& s1,Seg& s2){
    return DiffSide(s1,s2) && DiffSide(s2,s1); 
}

bool IsValid(){
    for(int i = 2; i < N-1; i++){
        if(SegCross(segs[0],segs[i])){
            //cout << 0 <<" " << i << endl;
            return false;
        }
    }
    for(int i = 1; i < N -2; i++){
        for(int j = i+2; j < N; j++){
            if(SegCross(segs[i],segs[j])){
                //cout << i << " " << j << endl;
                return false;
            }
        }
    }
    return true;
}

bool IsSame(const Point& a, const Point& b){
    if(fabs(a.x_ - b.x_) >= EPS) return 0;
    if(fabs(a.y_ - b.y_) >= EPS) return 0;
    return 1;
}

bool Seen(const Seg& a, int index){
    if(IsSame(a.st_,a.end_)) return 0;// a is short enough and seen as a point;
    Seg leye,reye;
    leye.st_ = eye; leye.end_ = a.st_;
    reye.st_ = eye; reye.end_ = a.end_;
    bool ok = 0;
    for(int i = 0; i < N; i++){
        if(i == index) continue;
        bool t1 = SegCross(leye,segs[i]);
        bool t2 = SegCross(reye,segs[i]);
        if(t1&&t2) return 0;
        //Note if any other segment didn't cross leye and reye,then ok should be 0 
        //and  seg a is seen.You can't just write ok = t1 || t2;
        ok |= t1 || t2;
    }
    if(!ok) return 1;
    Seg a_l,a_r;
    Point mid((a.st_.x_+a.end_.x_)/2,(a.st_.y_+a.end_.y_)/2);    
    a_l.st_ = a.st_; a_l.end_ = mid;
    a_r.st_ = mid; a_r.end_ = a.end_;
    if(Seen(a_l,index)) return 1;
    if(Seen(a_r,index)) return 1;
    return 0; 
}

int main(){
    fin >> N;
    double x = 0, y= 0;
    fin >> x >> y;
    //Point eye(x,y);
    eye.x_ = x; eye.y_ = y;
    fin >> x >> y;
    Point st(x,y); 
    for(int i = 0; i < N-1; i++){
        fin >> x >> y;
        Point end(x,y);
        segs[i].st_ = st;segs[i].end_ = end;
        st = end;
    }
    //For output requestment;
    segs[N-1].st_ = segs[0].st_; segs[N-1].end_ = st;
    if(!IsValid()){cout <<"NOFENCE"<< endl; return 0;}
    int seen_num = 0;
    for(int i = 0; i < N; i++){
        if(Seen(segs[i],i)){
           segs_seen[i] = 1;
           seen_num++;
        } 
    }
    cout << seen_num << endl;
    for(int i = 0; i < N-2; i++){
        if(segs_seen[i])
            cout << segs[i].st_.x_<<" "<<segs[i].st_.y_<<" "<<segs[i].end_.x_<<" "<<segs[i].end_.y_ << endl;
    }
    //Consider the output requestment, only the last segment is no qualified.
    if(segs_seen[N-1])
        cout << segs[N-1].st_.x_<<" "<<segs[N-1].st_.y_<<" "<<segs[N-1].end_.x_<<" "<<segs[N-1].end_.y_ << endl;
    if(segs_seen[N-2])
        cout << segs[N-2].st_.x_<<" "<<segs[N-2].st_.y_<<" "<<segs[N-2].end_.x_<<" "<<segs[N-2].end_.y_ << endl;
    return 0;
}
