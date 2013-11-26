/*
ID: cmykrgb1
PROG: rect1
LANG: C
*/
#include <stdio.h>
#define MAX 1001

typedef struct 
{
    long px,py,qx,qy,color;
}rectangular;

FILE *fi,*fo;
long A,B,n,cur_c;
long sq[MAX];
rectangular R[MAX];

void compute(long px,long py,long qx,long qy,long posi)
{
    do posi++; 
    while (posi<=n && 
    ( R[posi].px>=qx || 
    R[posi].py>=qy || 
    R[posi].qx<=px || 
    R[posi].qy<=py ) );
    if (posi>n) //未找到重叠部分
        sq[cur_c]+=(qx-px)*(qy-py);
    else        //有重叠部分 拆分矩形
    {
        if (px<R[posi].px)
        {
            compute(px,py,R[posi].px,qy,posi);
            px=R[posi].px;
        }
        if (qx>R[posi].qx)
        {
            compute(R[posi].qx,py,qx,qy,posi);
            qx=R[posi].qx;
        }
        if (py<R[posi].py)
            compute(px,py,qx,R[posi].py,posi);  
        if (qy>R[posi].qy)
            compute(px,R[posi].qy,qx,qy,posi); 
    }
}

int main(void)
{
    long i;
    long px,py,qx,qy,color;
    fi=fopen("rect1.in","r");
    fo=fopen("rect1.out","w");
    fscanf(fi,"%ld%ld%ld",&A,&B,&n);
    for (i=1;i<=n;i++)
    {
        fscanf(fi,"%ld%ld%ld%ld%ld",
        &px,&py,&qx,&qy,&color);
        R[i].px=px;
        R[i].py=py;
        R[i].qx=qx;
        R[i].qy=qy;
        R[i].color=color;
    }
    R[0].qx=A;R[0].qy=B;R[0].color=1;
    for (i=n;i>=0;i--)
    {
        cur_c=R[i].color;
        compute(R[i].px,R[i].py,R[i].qx,R[i].qy,i);
    }
    for (i=1;i<MAX;i++)
        if (sq[i])
            fprintf(fo,"%ld %ld\n",i,sq[i]);
    fclose(fi);
    fclose(fo);
    return 0;
}
