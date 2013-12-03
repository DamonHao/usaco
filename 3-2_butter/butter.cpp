/*
Main idea:
Use SPFA(i) to compute the shortest paths from single source i; 
i is in [1..P], P is the number of pastures; and then compute the total 
distance of paths each cow to source i;  
SPFA means Shortest Path Faster Algorithm, detail can refer to nocow;
You can also use Dijkstra to get the shortest paths, but its implement 
is more difficult, because the operation of priority queue;
*/
/*
 Executing...
   Test 1: TEST OK [0.000 secs, 8512 KB]
   Test 2: TEST OK [0.000 secs, 8512 KB]
   Test 3: TEST OK [0.011 secs, 8512 KB]
   Test 4: TEST OK [0.011 secs, 8512 KB]
   Test 5: TEST OK [0.011 secs, 8512 KB]
   Test 6: TEST OK [0.032 secs, 8512 KB]
   Test 7: TEST OK [0.043 secs, 8512 KB]
   Test 8: TEST OK [0.086 secs, 8512 KB]
   Test 9: TEST OK [0.173 secs, 8512 KB]
   Test 10: TEST OK [0.140 secs, 8512 KB]

All tests OK.
*/
/*
ID: haolink1
PROG: butter
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

const unsigned int INF = ~0;
int N = 0, P = 0, C = 0;
unsigned int dist[800];
short cow[800];
int edge_num[800];
int edge_end[800][800];
unsigned int weight[800][800];
bool in_queue[800];
ifstream fin("butter.in");
ofstream cout("butter.out");

void SPFA(int source){
    queue<int> que;
    //Note the usage of memset;
    memset(in_queue,0,sizeof(in_queue));
    memset(dist,INF,sizeof(dist));
    que.push(source);
    in_queue[source] = true;
    dist[source] = 0;
    while(!que.empty()){
        int cur = que.front();
        que.pop();
        in_queue[cur] = false;
        for(int i = 0; i < edge_num[cur]; i++){
            int cur_end = edge_end[cur][i];
            if(dist[cur]+weight[cur][cur_end] < dist[cur_end]){
                dist[cur_end] = dist[cur]+weight[cur][cur_end];
                if(!in_queue[cur_end]){
                    que.push(cur_end);
                    in_queue[cur_end] = true;
                }
            }
        }    
    }
}

unsigned int TotalDist(){
    unsigned int total = 0;
    for(int i = 0; i < N; i++){
        total += dist[cow[i]]; 
    } 
    return total;
}

int main(){
    fin >> N >> P >> C;
    for(int i = 0; i < N; i++){
        int pasture_num = 0;
        fin >> pasture_num;
        cow[i] = --pasture_num; 
    } 
    for(int i = 0; i < C; i++){
        int u = 0,v = 0,w = 0;
        fin >> u >> v;
        u--;v--;
        edge_end[u][edge_num[u]] = v;
        edge_end[v][edge_num[v]] = u;
        edge_num[u]++;
        edge_num[v]++;
        fin >> w;
        weight[u][v] = weight[v][u] = w;
    }
    unsigned int min_total_dist = INF;
    for(int i = 0; i < P; i++){
        SPFA(i);
        unsigned int cur_total_dist = TotalDist();
        if(cur_total_dist < min_total_dist)
            min_total_dist = cur_total_dist;
    }
    cout << min_total_dist << endl;
    return 0;
}


