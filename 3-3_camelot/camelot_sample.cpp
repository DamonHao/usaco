/*
ID: huilong1
LANG: C++
TASK: camelot
*/
#include<stdio.h>
#include<stdlib.h>
 
#define LENQUE 781
#define INFI 500
FILE *fin,*fout;
int R,C;
int dist[781][31][27];
int total[31][27];
int distking[31][27];
int distride[120][31][27];
int numride;
int king[2];
int numknight;
int knight[781][2];
int moveknight[8][2]={
        {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}
};
int moveking[8][2]={
        {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
};
int queue[LENQUE][3];
bool done[31][27];
 
void bfs(int s[2],int move[8][2],int distmemo[31][27]){
        int i,j;
        for(i=0;i<R;i++)for(j=0;j<C;j++)done[i][j]=false;
        for(i=0;i<R;i++)for(j=0;j<C;j++)distmemo[i][j]=INFI;
        distmemo[s[0]][s[1]]=0;
        done[s[0]][s[1]]=true;
        int head=0,tail=1;
        queue[0][0]=s[0];
        queue[0][1]=s[1];
        queue[0][2]=0;
        while(head!=tail){
                for(i=0;i<8;i++){
                        int temp[2];
                        temp[0]=queue[head][0]+move[i][0];
                        temp[1]=queue[head][1]+move[i][1];
                        if(temp[0]>=0&&temp[0]<R&&temp[1]>=0&&temp[1]<=C){
                                if(!done[temp[0]][temp[1]]){
                                        queue[tail][0]=temp[0];
                                        queue[tail][1]=temp[1];
                                        queue[tail][2]=queue[head][2]+1;
                                        done[temp[0]][temp[1]]=true;
                                        distmemo[temp[0]][temp[1]]=queue[tail][2];
                                        tail=(tail+1)%LENQUE;
                                }
                        }
                }
                head=(head+1)%LENQUE;
        }
}
 
int main(){
        fin=fopen("camelot.in","r");
        fout=fopen("camelot.out","w");
        fscanf(fin,"%d %d\n",&R,&C);
        char col;
        int row;
        fscanf(fin,"%c %d",&col,&row);
        king[0]=row-1;
        king[1]=col-'A';
        while(fscanf(fin,"%c",&col)!=EOF){
                if(col==' '||col=='\n')continue;
                fscanf(fin,"%d",&row);
                knight[numknight][0]=row-1;
                knight[numknight][1]=col-'A';
                numknight++;
        }
        int i;
        bfs(king,moveking,distking);
        for(i=0;i<8;i++){
                int temp[2];
                temp[0]=king[0]+moveking[i][0];
                temp[1]=king[1]+moveking[i][1];
                while(temp[0]>=0&&temp[0]<R&&temp[1]>=0&&temp[1]<C){
                        bfs(temp,moveknight,distride[numride++]);
                        temp[0]=temp[0]+moveking[i][0];
                        temp[1]=temp[1]+moveking[i][1];
                }
        }
        bfs(king,moveknight,distride[numride++]);
        for(i=0;i<numknight;i++){
                bfs(knight[i],moveknight,dist[i]);
        }
        int min=0x7fffffff;
        int gr,gc,ride,d,move;
        for(gr=0;gr<R;gr++)for(gc=0;gc<C;gc++){
                for(i=0;i<numknight;i++){
                        total[gr][gc]+=dist[i][gr][gc];
                }
        }
        for(gr=0;gr<R;gr++)for(gc=0;gc<C;gc++){
                d=distking[gr][gc]+total[gr][gc];
                if(d<min)min=d;
                for(ride=0;ride<numknight;ride++){
                        d=distride[numride-1][gr][gc];
                        d+=dist[ride][king[0]][king[1]];
                        d+=total[gr][gc]-dist[ride][gr][gc];
                        if(d<min)min=d;
                        int po=0,countking=0;
                        for(i=0;i<8;i++){
                                int temp[2];
                                temp[0]=king[0]+moveking[i][0];
                                temp[1]=king[1]+moveking[i][1];
                                countking=1;
                                while(temp[0]>=0&&temp[0]<R&&temp[1]>=0&&temp[1]<C){
                                        d=distride[po][gr][gc];
                                        d+=countking;
                                        d+=dist[ride][temp[0]][temp[1]];
                                        d+=total[gr][gc]-dist[ride][gr][gc];
                                        if(d<min)min=d;
                                        po++;
                                        countking++;
                                        temp[0]=temp[0]+moveking[i][0];
                                        temp[1]=temp[1]+moveking[i][1];
                                }
                        }
                }
        }
        fprintf(fout,"%d\n",min);
        return 0;
}
