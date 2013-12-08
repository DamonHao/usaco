/*
Main Idea;
dist[x1][y1][x2][y2] denote the knight's min move from (x1,y1) to (x2,y2);
king_move_num[x][y] denote the king's min move from its initial place to the 
square it meet a knight.We can compute both of them by BFS;
total_dist[x][y] denote the total cost for king and knight to meet at square (x,y);
We choose the knight whose move "increase" lest to pick up king; Assume they meet at (x1,y1) and the
target square all knight and king meet is (x2,y2)
This knight and king's cost is dist[init_x][init_y][x1][y1] + dist[x1][y1][x2][y2] + king_move_num[x1][y1];
Note, we only cosider the range king and knight meet is +/-2 from king's initial place;
For knight i who don't pick up king, their cost is dist[x1][y1][x2][y2]; 
Sum all the cost we get total_dist[x2][y2];
Then we choose the min dist from total_dist;
*/
/*
Executing...
   Test 1: TEST OK [0.000 secs, 5900 KB]
   Test 2: TEST OK [0.000 secs, 5900 KB]
   Test 3: TEST OK [0.000 secs, 5900 KB]
   Test 4: TEST OK [0.011 secs, 5900 KB]
   Test 5: TEST OK [0.086 secs, 5900 KB]
   Test 6: TEST OK [0.130 secs, 5900 KB]
   Test 7: TEST OK [0.000 secs, 5900 KB]
   Test 8: TEST OK [0.000 secs, 5900 KB]
   Test 9: TEST OK [0.043 secs, 5900 KB]
   Test 10: TEST OK [0.205 secs, 5900 KB]
   Test 11: TEST OK [0.000 secs, 5900 KB]
   Test 12: TEST OK [0.000 secs, 5900 KB]
   Test 13: TEST OK [0.000 secs, 5900 KB]
   Test 14: TEST OK [0.000 secs, 5900 KB]
   Test 15: TEST OK [0.000 secs, 5900 KB]
   Test 16: TEST OK [0.000 secs, 5900 KB]
   Test 17: TEST OK [0.000 secs, 5900 KB]
   Test 18: TEST OK [0.000 secs, 5900 KB]
   Test 19: TEST OK [0.000 secs, 5900 KB]
   Test 20: TEST OK [0.000 secs, 5900 KB]

All tests OK.
*/
/*
ID: haolink1
PROG: camelot
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
using namespace std;
ifstream fin("camelot.in");
ofstream cout("camelot.out");
const int INF = 0x7FFFFFFF;
const int R_MAX = 30;
const int C_MAX = 26;
int R = 0, C = 0;
int move_knight[8][2] = {{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2}};
int move_king[8][2] = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};
class Posi{
public:
    int row_;
    int col_;
    Posi():row_(0),col_(0){}
    Posi(const Posi& cur){
        row_ = cur.row_;
        col_ = cur.col_;
    }
    Posi(int row,int col):row_(row),col_(col){}
};
Posi king;
Posi king_range[25];
int range_num = 0;
Posi knight[780];
int knight_num = 0;
int dist[R_MAX][C_MAX][R_MAX][C_MAX];
int total_dist[R_MAX][C_MAX];
int king_move_num[R_MAX][C_MAX];

void BFS(Posi& init,int move[][2]){
    if(dist[init.row_][init.col_][init.row_][init.col_] != -1)
        return;//This place has one knight and its dist has been compute;
    dist[init.row_][init.col_][init.row_][init.col_] = 0;    
    queue<Posi> my_queue;
    my_queue.push(init);
    while(!my_queue.empty()){
        Posi cur = my_queue.front();
        my_queue.pop();
        for(int i = 0; i < 8; i++){
            int row = cur.row_ + move[i][0];
            int col = cur.col_ + move[i][1];
            if(row >= 0 && row < R && col >= 0 && col < C && dist[init.row_][init.col_][row][col] == -1){
                dist[init.row_][init.col_][row][col] = dist[init.row_][init.col_][cur.row_][cur.col_] + 1;
                my_queue.push(Posi(row,col));
            }
        }
    }
} 
void KingBFS(Posi& init,int move[][2]){
    memset(king_move_num,0xFF,sizeof(king_move_num));
    king_move_num[init.row_][init.col_] = 0;    
    queue<Posi> my_queue;
    my_queue.push(init);
    while(!my_queue.empty()){
        Posi cur = my_queue.front();
        my_queue.pop();
        for(int i = 0; i < 8; i++){
            int row = cur.row_ + move[i][0];
            int col = cur.col_ + move[i][1];
            if(row >= 0 && row < R && col >= 0 && col < C && king_move_num[row][col] == -1){
                king_move_num[row][col] = king_move_num[cur.row_][cur.col_] + 1;
                my_queue.push(Posi(row,col));
            }
        }
    }
} 

int ChooseKnight(int row,int col,int& num_chosen){
    int min_dist = INF, min_inc = INF;
    for(int i = 0; i < knight_num; i++){
        for(int j = 0; j < range_num; j++){
            int kin_r = king_range[j].row_, kin_c = king_range[j].col_;
            int kni_r = knight[i].row_,kni_c = knight[i].col_; 
            int d1 = dist[kni_r][kni_c][kin_r][kin_c];
            int d2 = dist[kin_r][kin_c][row][col];
            if(d1 < 0 || d2 < 0) continue; //Note in some case, the knight can't reach all squares, like R = 2, C = 26;
            //Note the below is wrong;
//          int cur_dist = d1 + d2 + abs(kin_r-king.row_)+abs(kin_c-king.col_);
            int cur_dist = d1 + d2 + king_move_num[kin_r][kin_c];
            int cur_inc = cur_dist - dist[kni_r][kni_c][row][col]; 
            if(min_inc > cur_inc){// we choose the knight whose move increase lest to pick up king;
                min_inc = cur_inc;
                min_dist = cur_dist;
                num_chosen = i;
            }
        }
    }
    return min_dist;
}

int main(){
    //Init;
    fin >> R >> C;
    int row = 0; 
    char col = 'A';
    fin >> col >> row;
    king.row_ = row - 1;
    king.col_ = col - 'A';
    while(fin >> col >> row){
        knight[knight_num].row_ = row - 1;
        knight[knight_num].col_ = col - 'A';
        knight_num++;
    }
    memset(dist,0xFF,sizeof(dist));

    //For knight
    for(int i = 0; i < knight_num; i++){
        BFS(knight[i],move_knight);
    }
    //For king
    //Compute King's min move to any other squares by BFS;
    KingBFS(king,move_king);
    //Compute King's Range to meet knight, here we enumerate +/- 2 of King's intial place;
    for(int i = -2; i <= 2; i++){
        for(int j = -2; j <= 2; j++){
            row = king.row_ + i;
            col = king.col_ + j;
            if(row >= 0 && row < R && col >= 0 && col < C){
                king_range[range_num].row_ = row;
                king_range[range_num].col_ = col;
                range_num++;
            }
        }
    } 
    //Compute min move in King's range to other squares;
    for(int i = 0; i < range_num; i++){
        BFS(king_range[i],move_knight);
    }
    if(knight_num > 0){
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                int num_chosen = 0;
                total_dist[i][j] = ChooseKnight(i,j,num_chosen);
                for(int m = 0; m < knight_num; m++){
                    if(m == num_chosen) continue;
                    total_dist[i][j] += dist[knight[m].row_][knight[m].col_][i][j];
                }
            }
        }
    }
    int min_dist = INF;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(min_dist > total_dist[i][j])
                min_dist = total_dist[i][j];
        }
    }
    cout << min_dist << endl;
    return 0;
}

