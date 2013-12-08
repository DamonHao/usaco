/*
Main idea 
Find Euler Path, not circuit, so take care to choose a start node whose
degree is odd;
*/
/*
Executing...
   Test 1: TEST OK [0.000 secs, 3512 KB]
   Test 2: TEST OK [0.000 secs, 3512 KB]
   Test 3: TEST OK [0.000 secs, 3512 KB]
   Test 4: TEST OK [0.000 secs, 3512 KB]
   Test 5: TEST OK [0.000 secs, 3512 KB]
   Test 6: TEST OK [0.000 secs, 3512 KB]
   Test 7: TEST OK [0.011 secs, 3512 KB]
   Test 8: TEST OK [0.022 secs, 3512 KB]

All tests OK.
*/
/*
ID: haolink1
PROG: fence
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <list>
using namespace std;
const int MAX = 500;
list<int> edges [MAX];
int path[1025];
int path_pos = 0;

bool CompareValue(int e1, int e2){
    return e1 <= e2 ? true : false;
}

void FindPath(int cur_node){
    if(edges[cur_node].empty()){
        path[path_pos] = cur_node;
        path_pos++;
    }else{
        while(!edges[cur_node].empty()){
            int neighbor = edges[cur_node].front();
            //delete the edge to neighbor;
            edges[cur_node].pop_front();
            for(list<int>::iterator it = edges[neighbor].begin(); it != edges[neighbor].end(); it++){
                if(*(it) == cur_node){
                    edges[neighbor].erase(it); 
                    break;
                }
            }
            FindPath(neighbor);
        }
        path[path_pos] = cur_node;
        path_pos++;
    }
}


void FindEulerPath(){
   path_pos = 0; 
   //Choose the node whose degree is odd as start point;
   for(int i = 0; i < MAX; i++){
        if(edges[i].size()%2 == 1){
            FindPath(i);
            return;
        }
   }
   //If All nodes' degree is even, then choose the smallest num;
   for(int i = 0; i < MAX; i++){
        if(!edges[i].empty()){
            FindPath(i);
            return;
        }
   } 
}

int main(){
    int F = 0;
    ifstream fin("fence.in");
    ofstream cout("fence.out");
    fin >> F;
    for(int i = 0; i < F; i++){
        int u = 0, v = 0;
        fin >> u >> v;
        u--; v--;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for(int i = 0; i < MAX; i++){
        if(!edges[i].empty()){
            edges[i].sort(CompareValue);
        }
    }
    FindEulerPath();
    for(int i = F; i >= 0; i--){
        cout << path[i]+1 << endl;
    }
    return 0;
}
