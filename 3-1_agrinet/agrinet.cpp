/*
ID: haolink1
PROG: agrinet
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <list>
using namespace std;

class Edge{
public:
    int x_;
    int y_;
    int dist_;
    Edge(int x,int y, int dist):
        x_(x),y_(y),dist_(dist){}
};

list<Edge> nodes;
short set_num[100];
int N = 0;

bool CompareDist(Edge e1,Edge e2){
    if(e1.dist_ <= e2.dist_ )
        return 1;
    else return 0;
}

void Union(short x_set,short y_set){
    short min_set = x_set < y_set ? x_set : y_set;
    short max_set = x_set > y_set ? x_set : y_set;
    for(int i = 0; i < N; i++){
        if(set_num[i] == max_set){
            set_num[i] = min_set;
        }
    }
}


int MST_Kruskal(){
    int total_cost = 0;
    for(int i = 0; i < N; i++){
        set_num[i] = i;
    }
    nodes.sort(CompareDist);
//    for(list<Edge>::iterator it = nodes.begin(); it != nodes.end(); it++){
//        cout<<it->x_<<" "<<it->y_<<" "<<it->dist_<<endl;
//    }
    for(list<Edge>::iterator it = nodes.begin(); it != nodes.end(); it++){
        if(set_num[it->x_] != set_num[it->y_]){
            total_cost += it->dist_;
            Union(set_num[it->x_],set_num[it->y_]); 
        } 
    }
    return total_cost;
}

//Main idea
//Minimun Spannig Tree, we use Kruskal's algorithm;
int main(){
    ifstream fin("agrinet.in");
    fin >> N;
    int value = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fin >> value;
            if(j > i){
                nodes.push_back(Edge(i,j,value));            
            }
        }
    }
    ofstream fout("agrinet.out");
    fout<<MST_Kruskal()<<endl;
    return 0;
}


