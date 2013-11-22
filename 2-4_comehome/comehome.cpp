/*
ID: haolink1
PROG: comehome
LANG: C++
*/

//#include <iostream>
#include <fstream>

const int INF = 52 * 1000 + 1;
int min_path[52];
bool is_remove[52];
int dist[52][52];
using namespace std;

bool IsCapital(char x){
    if(x >= 'A' && x <= 'Z')
        return true;
    else return false;
}

int ExtractMin(){
    int min_index = -1;
    int min = INF; 
    for(int i = 0; i < 52; i++){
        if(min > min_path[i] && is_remove[i] == 0){
            min = min_path[i];
            min_index = i;
        }
    }
    if(min_index >= 0)
        is_remove[min_index] =1;
    return min_index;
}

void Relax(int x,int y){
    if(min_path[y] > min_path[x] + dist[x][y])
        min_path[y] = min_path[x] + dist[x][y];
}

void Dijkstra(){
    for(short i = 0; i < 52; i++){
        min_path[i] = INF;
    }
    min_path[25] = 0;
    while(1){
        int index = ExtractMin();
        if(index < 0)
            break;
        for(int i = 0; i < 52; i++){
            if(dist[index][i] < INF ){
                Relax(index,i); 
            }
        }
    }
}

//Main idea
//Calculate the shortest path from 'Z' to ohter pastures by  Dijkstra algorithm;
//And then choose shortest path among 'A' to 'Y';
int main(){
    for(short i = 0; i < 52; i++ ){
        for(short j = 0; j < 52; j++){
            dist[i][j] = INF;//Note dist[i][i] is also INF and it will be used in Dijkstra;
        }
    }
    int num = 0;
    ifstream fin("comehome.in");
    fin >> num;
    for(int i = 0; i < num; i++){
        int x, y;
        char x_char,y_char;
        int dis;
        fin >> x_char >> y_char >> dis;
        if(IsCapital(x_char)){
           x = x_char-'A';
        }else
            x = x_char - 'a' + 26;
        if(IsCapital(y_char))
            y = y_char-'A';
        else
            y = y_char- 'a' + 26;
        if(dis < dist[x][y] && x != y)//For each path between two pastures, we only take the shortest;
            dist[x][y] = dist[y][x] = dis;
    }
    Dijkstra();
    int min = INF;
    int index = -1;
    for(int i = 0; i < 25; i++){
        if(min_path[i] < min){
            min = min_path[i];
            index = i;
        }
    }
    char cow = 'A' + index;
    ofstream fout("comehome.out");
    fout << cow <<" "<< min << endl;
    return 0;
}
