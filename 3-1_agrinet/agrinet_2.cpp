/*
ID: haolink1
PROG: agrinet
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

const int INF = 100001;
int N = 0;
bool is_visited[100];
int node_key[100];
int dist[100][100];
//parent[i] denotes i's parent node;
//Start from node 0, so the parent[i]'s initial value can be 0;    
int parent[100];

int ExtractMin(){
    int index = -1;
    int min = INF;
    for(int i = 0; i < N; i++){
        if(node_key[i] < min && is_visited[i] == 0){
            min = node_key[i];
            index = i;
        } 
    }
    //Note if you set index > 0, there will be a endless loop;
    if(index >= 0)
        is_visited[index] = 1;
    return index;
}

int MST_Prim(){
    for(int i = 0; i < N; i++){
        node_key[i] = INF;
    }
    node_key[0] = 0; 
    int total_cost = 0;
    while(1){
        int i = ExtractMin();
        if(i < 0)
            break;
        if(parent[i] != i)
            total_cost += dist[parent[i]][i];
        for(int j = 0; j < N; j++){
            if(i != j && dist[i][j] < node_key[j]){
                node_key[j] = dist[i][j];
                //Note record j's parent to calculate the distance;
                //Start from node 0, so the parent[i]'s initial value can be 0;    
                parent[j] = i;             
            }

        }
    }
    return total_cost;
}

//Main idea
//Minimun Spannig Tree, we use Prim's algorithm;
int main(){
    ifstream fin("agrinet.in");
    fin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fin >> dist[i][j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    } 
    ofstream fout("agrinet.out");
    cout<<MST_Prim()<<endl;
    return 0;
}


