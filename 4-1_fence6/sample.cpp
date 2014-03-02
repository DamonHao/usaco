#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <climits>
#include <cstring>

using namespace std;

ifstream fin("fence6.in");
ofstream fout("fence6.out");

#ifdef _DEBUG
#define out cout
#define in cin
#else
#define out fout
#define in fin
#endif

struct Edge{
    int va,vb,len;
};

int edge_num;
int vertex_num;
int graph[100][100];
Edge edges[100];

int get_vertex(set<int>&s)
{
    static map<set<int>,int>vertex;

    if( vertex.find(s) == vertex.end() ){
        vertex[s] = vertex_num;
        return vertex_num++;
    }else{
        return vertex[s];
    }
}

void build_graph()
{
    in>>edge_num;

    for(int i=0;i<100;++i)
        for(int j=0;j<100;++j)
            graph[i][j] = INT_MAX/2;

    for(int i=0;i<edge_num;++i){
        int edge,tmp,len;
        int left_num,right_num;
        set<int> s;
        in>>edge>>len>>left_num>>right_num;
        s.insert(edge);
        for(int j=0;j<left_num;++j){
            in>>tmp;
            s.insert(tmp);
        }
        int left_vertex = get_vertex(s);
        s.clear();
        s.insert(edge);
        for(int j=0;j<right_num;++j){
            in>>tmp;
            s.insert(tmp);
        }
        int right_vertex = get_vertex(s);
        graph[left_vertex][right_vertex] = 
            graph[right_vertex][left_vertex] = len;
        edges[i].va = left_vertex;
        edges[i].vb = right_vertex;
        edges[i].len = len;
    }
}

int shortest_path(int va,int vb)
{
    int shortest[100];
    bool visited[100];

    memset(visited,0,sizeof(visited));
   
    for(int i=0;i<vertex_num;++i){
        shortest[i] = graph[va][i];
    }

    visited[va] = true;

    while(true){
        int m = -1;
        for(int i=0;i<vertex_num;++i){
              if(!visited[i]){
                if(m==-1||shortest[i]<shortest[m])
                    m = i;
              }
        }
        //没有新加结点了
        
        visited[m] = true;

        if( m==vb )
            return shortest[vb];

        for(int i=0;i<vertex_num;++i){
            if(!visited[i])
            shortest[i] = min(shortest[i],shortest[m]+graph[m][i]);
        }
    }
}

void solve()
{
    build_graph();

    int best = INT_MAX;

    for(int i=0;i<edge_num;++i){
      graph[edges[i].va][edges[i].vb] = graph[edges[i].vb][edges[i].va] = INT_MAX/2; 
      best = min(best,edges[i].len+shortest_path(edges[i].va,edges[i].vb) );
      graph[edges[i].va][edges[i].vb] = graph[edges[i].vb][edges[i].va] = edges[i].len; 
    }

    out<<best<<endl;
}

int main(int argc,char *argv[])
{
    solve(); 
    return 0;
}
