/*
        ID:ymf11111
        TASK:fence4
        LANG:C++
*/
 
//by ymfoi(ymf)
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define MAXE 10000
#define EPS 1e-6
 
using namespace std;
 
typedef
struct Point {
        double px,py;
} Vect;
 
struct Seg {
        Point  st,ed;
};
 
double det(Vect a,Vect b) {
        return (a.px * b.py - b.px * a.py);
}
 
Vect P2Vect(Point a,Point b) { // a --> b
        b.px -= a.px;
        b.py -= a.py;
        return b;
}
 
bool Diff_Side(Seg a,Seg b) {
 
        Vect va = P2Vect(a.st,a.ed);
        double t1 = det(va,P2Vect(a.st,b.st));
        double t2 = det(va,P2Vect(a.st,b.ed));
        if (t1 * t2 <= 0) return 1;
        return 0;
}
 
bool Seg_Cross(Seg a,Seg b) {
        return (Diff_Side(a,b) && Diff_Side(b,a));
}
 
bool Same(Point a,Point b) {
 
        if (fabs(a.px - b.px) >= EPS) return 0;
        if (fabs(a.py - b.py) >= EPS) return 0;
        return 1;
}
//////////// Basic Graphics  ///////////////
 
Seg edges[MAXE];
int e_Num = 0;
bool canbs[MAXE];
Point eye;
 
bool seen(Seg a,int num,Point eye) { //二分法！ 通过了test12 且通过网友自编数据
 
        if (Same(a.st,a.ed)) return 0; // a is a point
 
        Seg leyes,reyes,al,ar;
        leyes.st = reyes.st = eye;
        leyes.ed = a.st; reyes.ed = a.ed;
        bool ok = 0;
 
        for (int i = 1; i <= e_Num; i++)
                if (i != num)
                {
                        bool b1 = Seg_Cross(leyes,edges[i]);
                        bool b2 = Seg_Cross(reyes,edges[i]);
                        if (b1 && b2) return 0;//cout << num <<"was covered by"<< i<<endl; }
                        ok|=b1 || b2;
                }
 
        if (!ok) return 1;
 
        al.st = a.st;
        al.ed.px = (a.st.px + a.ed.px) / 2;
        al.ed.py = (a.st.py + a.ed.py) / 2;
        ar.st = al.ed;
        ar.ed = a.ed;
 
        if (seen(al,num,eye)) return 1;
        if (seen(ar,num,eye)) return 1;
        return 0;
}
 
int main() {
 
        int N,sum = 0;
        Point lp;
 
        freopen("fence4.in","r",stdin);
        freopen("fence4.out","w",stdout);
                memset(canbs,0,sizeof(canbs));
 
        scanf("%d",&N);
        scanf("%lf %lf",&eye.px,&eye.py);
        scanf("%lf %lf",&lp.px,&lp.py);
 
        for (int i = 2; i <= N; i++)
        {
                Point tmp;
                scanf("%lf %lf",&tmp.px,&tmp.py);
                edges[++e_Num].st = lp;
                edges[e_Num].ed = tmp;
                lp = tmp;
        }
        edges[++e_Num].st =lp;
        edges[e_Num].ed = edges[1].st;
 
        //read & add
 
                for (int i = 1; i <= e_Num; i++) if (canbs[i] = seen(edges[i],i,eye)) sum++;
 
 
                printf("%d\n",sum);
        for (int i = 1; i <= e_Num - 2; i++)
                if (canbs[i])
                        printf("%.0lf %.0lf %.0lf %.0lf\n",edges[i].st.px,edges[i].st.py,edges[i].ed.px,edges[i].ed.py);
                if (canbs[e_Num])
                printf("%.0lf %.0lf %.0lf %.0lf\n",edges[e_Num].ed.px,edges[e_Num].ed.py,edges[e_Num].st.px,edges[e_Num].st.py);
                if (canbs[e_Num - 1])
                printf("%.0lf %.0lf %.0lf %.0lf\n",edges[e_Num - 1].st.px,edges[e_Num - 1].st.py,edges[e_Num - 1].ed.px,edges[e_Num - 1].ed.py);
 
       return 0;
}
