/*
ID: haolink1
PROG: cowtour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <math.h>       /* sqrt */
#include<iomanip> //std::setiosflags
#define INF (1e40) 

using namespace std;

short num =0;
//dis[i][j] means the shortest distance between i,j;
//dis_max[i] means the max distance of shortest path start from i;
double dis[150][150],dis_max[150];
int px[150],py[150];

double dist(int x1,int y1,int x2,int y2){
    return sqrt(double(x1-x2)*(x1-x2) + double(y1-y2)*(y1-y2)); 
}

void floyd(){
    for(short k = 0; k < num; k++){
        for(short i = 0; i < num; i++){
            for(short j =0; j < num; j++){
                if(dis[i][k]+dis[k][j] < dis[i][j])
                    dis[i][j] = dis[i][k]+dis[k][j];
            }
        }
    }
    //Note: reset the dis[i][i] to INF in case
    //it will influence the dis_max[i];
    for(short i = 0; i < num; i++){
        dis[i][i] = INF;
    }
}
/*
void PrintDist(){
    for(short i = 0; i < num; i++){
        for(short j = 0; j < num; j++){
            cout<< dis[i][j] <<" ";
        }
        cout << endl;
    }
    
}
*/

//Main Idea
//Use floyd algorithm to calculate shortest path of each pair of pastures 
//The compute the smallest possible diameter of the new connected field by enumeration
//The key point is that there are exactly two field need to be connected;
int main(){
    ifstream fin("cowtour.in");
    fin >> num;
    for(short i = 0; i < num; i++){
        fin >> px[i];
        fin >> py[i];
    }
    for(short i = 0; i < num; i++){
        char val[150];
        fin >> val;
        for(short j = 0; j < num; j++){
            if(val[j] == '1'){
                dis[i][j] = dist(px[i],py[i],px[j],py[j]);
            }else{
                dis[i][j] = INF;
            }
        }
    }
    //PrintDist();
    floyd();
    //PrintDist();
    double d_max = 0;
    for(short i = 0; i < num; i++){
        double tmp_max = 0;
        for(short j = 0; j < num; j++){
            if(dis[i][j] > tmp_max && dis[i][j] < INF) 
                tmp_max = dis[i][j];
        }
        dis_max[i] = tmp_max;
        if(tmp_max > d_max)
            d_max = tmp_max;
    }
    double d_min = INF;
    for(short i = 0; i < num-1; i++){
        for(short j = i+1; j < num; j++){
            if(i != j && dis[i][j] == INF){
                double temp = dist(px[i],py[i],px[j],py[j]);
                if(temp+dis_max[i]+dis_max[j] < d_min)
                    d_min = temp+dis_max[i]+dis_max[j];
            }
        }
    }
    ofstream fout("cowtour.out");
    //fout <<setiosflags(ios::fixed)<<setiosflags(ios::right)<<setprecision(6)<<(d_max > d_min ? d_max:d_min) << endl;
    fout <<setiosflags(ios::fixed)<<setprecision(6)<<(d_max > d_min ? d_max:d_min) << endl;
    return 0;
}
