/*
    这题是求无向图中的一个最小环的长度。
主要思路是：因为边都是直线，边的两点之间的最短距离必然是这个边长。那么，
再求一条到两顶点的最短距径，这个路径与边构成了一个环。这个环是包含该边的最小环。
枚举一下所有边，计算出最小环即可。对于每个边，删除该边，然后计算两顶点的最短路径，再恢复该边。
    但是这个图的输入是用边表示的，一个难点就是将其转换成用点表示。这里用边的集合来表示一个点。
然后用map<set<int>,int>来存储某一边对应的边的编号。每找到一个新的顶点则分配一个新的编号。这部
分主要通过函数get_vertex(set<int>&s)来实现。
refer to 止于自娱
*/
/*
Executing...
   Test 1: TEST OK [0.000 secs, 3552 KB]
   Test 2: TEST OK [0.011 secs, 3552 KB]
   Test 3: TEST OK [0.011 secs, 3552 KB]
   Test 4: TEST OK [0.011 secs, 3552 KB]
   Test 5: TEST OK [0.011 secs, 3552 KB]
   Test 6: TEST OK [0.011 secs, 3552 KB]
   Test 7: TEST OK [0.011 secs, 3552 KB]
   Test 8: TEST OK [0.022 secs, 3552 KB]
   Test 9: TEST OK [0.022 secs, 3552 KB]

All tests OK.
Your program ('fence6') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations!
*/

/*
ID: haolink1
PROG: fence6
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

ifstream fin("fence6.in");
ofstream cout("fence6.out");

class Edge{public: int va_,vb_,len_;};
const int INF = 0x7fffffff/2;
const int MAX = 100; 
int edge_num;
int vertex_num;
int graph[MAX][MAX];
Edge edges[MAX];

int GetVertex(set<int>& s){
    static map<set<int>,int> vertexs;
    if(vertexs.find(s) == vertexs.end()){
        vertexs[s] = vertex_num;
        return vertex_num++;
    }else return vertexs[s];
}

void BuildGraph(){
    fin >> edge_num; 
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            graph[i][j] = INF;
        }
    }
    for(int i = 0; i < edge_num; i++){
        int cur_edge = 0,len = 0,l_num = 0,r_num = 0,tmp = 0;
        fin >> cur_edge >> len >> l_num >> r_num;
        set<int> s;
        s.insert(cur_edge);
        for(int j = 0; j < l_num; j++){
            fin >> tmp;
            s.insert(tmp);
        }
        int l_v = GetVertex(s);
        s.clear();
        s.insert(cur_edge);
        for(int j = 0; j < r_num; j++){
            fin >> tmp;
            s.insert(tmp);
        }
        int r_v = GetVertex(s);
        graph[l_v][r_v] = graph[r_v][l_v] = len;
        edges[i].va_ = l_v; edges[i].vb_ = r_v; edges[i].len_ = len;
    }
}
int v_dist[MAX];
bool v_visited[MAX];

int ExtractMin(){
    int min = INF,index = -1;
    for(int i = 0; i < vertex_num; i++){
        if(v_visited[i] == 0 && v_dist[i] < min ){
            min = v_dist[i];
            index = i;
        }
    }
    if(index != -1) v_visited[index] = 1;
    return index;
}

int DIJKSTRA(int source, int des){
    for(int i = 0; i < vertex_num; i++){
        v_dist[i] = INF;
        v_visited[i] = 0;
    }
    v_dist[source] = 0;
    while(1){
        int cur_v = ExtractMin(); 
        if (cur_v == des)//Note this case means source can reach des, also use it for efficiency;
            return v_dist[des];
        else if(cur_v == -1) //Note this case means source cannot reach des;
            return INF;
        for(int i = 0; i < vertex_num; i++){
            if(v_dist[i] > v_dist[cur_v] + graph[cur_v][i])
                v_dist[i] = v_dist[cur_v] + graph[cur_v][i];
        }          
    }
}

int main(){
    BuildGraph();
    int min_perimeter = INF; 
    //int min_index = -1;
    for(int i = 0; i < edge_num; i++){
        int va = edges[i].va_,vb = edges[i].vb_;
        int len = graph[va][vb];
        graph[va][vb] = graph[vb][va] = INF;
        int min_path = DIJKSTRA(va,vb);
        if(min_perimeter > len + min_path){ 
            min_perimeter = len + min_path;
      //      min_index = i;
        }
        //Note to retore;
        graph[va][vb] = graph[vb][va] = len;
    }
    
    //cout << min_index << endl;
    cout << min_perimeter << endl;
    return 0;
}

