#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N,R;
int rail[1024];
int board[50];
int boardsum;
int railsum[1024];

int cmp1(const void *a,const void *b)  //large to small
{
    return(*(int *)a < *(int *)b);
}

int cmp2(const void *a,const void *b)  //small to large
{
    return(*(int *)a > *(int *)b);
}

void init()
{
    scanf("%d",&N);
    int i;
    for(i = 0;i < N;i ++)
    {
        scanf("%d",&board[i]);
        boardsum += board[i];
    }
    qsort(board,N,sizeof(int),cmp1);
    scanf("%d\n",&R);
    for(i = 0;i < R;i ++)
    {
        scanf("%d",&rail[i]);
    }
    qsort(rail,R,sizeof(int),cmp2);
    //ignore impossible boards and rails
    while(rail[R - 1] > board[0] && R > 0)    R --;
    while(N > 0 && board[N - 1] < rail[0])    N --;
    if(R == 0 || N == 0)   //无解的特殊情况
    {
        printf("0\n");
        fclose(stdout);
        exit(0);
    }
    railsum[0] = rail[0];
    for(i = 1;i < R;i ++)
    {
        railsum[i] = railsum[i - 1] + rail[i];
    }
}

int cut_rail_from[1030];
int max_waste,cur_waste;
int dfs_check(int index)
{
    int start,i,r;
    if(cur_waste > max_waste)    return 0;
    if(index < 0)
    {
        return 1;
    }
    if(rail[index] == rail[index + 1])
    {
        start = cut_rail_from[index + 1];
    }
    else start = 0;
    
    for(i = start;i < N;i ++)
    {
        if(board[i] >= rail[index])
        {
            board[i] -= rail[index];
            cut_rail_from[index] = i;
            if(board[i] < rail[0])    cur_waste += board[i];
            r = dfs_check(index - 1);
            if(board[i] < rail[0])    cur_waste -= board[i];
            board[i] += rail[index];
            cut_rail_from[index] = -1;
            if(r == 1)    return 1;
        }
    }
    return 0;
}

void binary()
{
    int i;
    for(i = 0;i < R;i ++)
        cut_rail_from[i] = -1;
    int l,r,mid;
    l = 0;
    r = R - 1;
    for(r = R - 1;r >= 0 && railsum[r] > boardsum;r --);
    while(l < r)
    {
        mid = (l + r + 1) / 2;       //向上取整
        max_waste = boardsum - railsum[mid];
        cur_waste = 0;
        if(dfs_check(mid))
            l = mid;
        else    r = mid - 1;
    }
    printf("%d\n",l + 1);
}

int main()
{
    freopen("fence8.in","r",stdin);
    freopen("fence8.out","w",stdout);
    init();
    binary();
    return 0;
}
