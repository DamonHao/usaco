/*
ID: haolink1
PROG: packrec
LANG: C++
*/
//#include <iostream>
#include <fstream>
#include <vector>       // std::vector
#include <algorithm>    // std::sort
using namespace std;
typedef unsigned int u_int;
class Rect{
public:
    int hight_;
    int width_;
    Rect(int hight,int width):hight_(hight),width_(width){}
    int Area()const{return hight_ * width_;}
    void Swap(){
        int temp = hight_;
        hight_ = width_;
        width_ = temp;
    }
    bool operator==(const Rect& rect){
        if(hight_ == rect.hight_ && width_ == rect.width_)
            return true;
        else return false;
    }
    void Format(){
        if(hight_ > width_)
            Swap();
    }
};

bool CompareRect(const Rect first,const Rect second){
    if(first.Area() < second.Area())
        return true;
    else return false;
}

bool CompareRectHight(const Rect first,const Rect second){
    if(first.hight_ <= second.hight_)
        return true;
    else return false;
}

int Max(int first,int second){
    if(first > second)
        return first;
    else return second;
}

void AddUnique(vector<Rect>& target_rects,Rect rect){
    //format the hight and width to compare;
    rect.Format();
    for(u_int i = 0; i < target_rects.size(); i++){
        if(target_rects[i] == rect)
            return;
    }
    target_rects.push_back(rect);
}

void CheckAreaToAdd(vector<Rect>& target_rects,int hight,int width,u_int& min_area){
    u_int area = hight * width;
    if(area == min_area){
        AddUnique(target_rects,Rect(hight,width));
    }else if(area < min_area){
        min_area = area;
        target_rects.clear();
        AddUnique(target_rects,Rect(hight,width));
    }
}

int main(){
    ifstream fin("packrec.in");
    int hight = 0;
    int width = 0;
    vector<Rect> rects;
    for(int i = 0; i < 4; i++){
        fin>>hight;
        fin>>width;
        Rect rect(hight,width);
        rects.push_back(rect);
    }
    //sort the element in ascending order;
    sort(rects.begin(),rects.end(),CompareRect);
    u_int min_area = -1;
    vector<Rect> target_rects;
    //type 1.And in type 1, all the four retangles are symmetric,
    //and no need to perform full permutation
    for(int i = 0; i < 2; i++){
        rects[0].Swap();
        for(int j = 0; j < 2; j++){
            rects[1].Swap();
            for(int m = 0; m < 2; m++){
                rects[2].Swap();
                for(int n = 0; n < 2; n++){
                    rects[3].Swap();
                    hight = Max(Max(rects[0].hight_,rects[1].hight_),Max(rects[2].hight_,rects[3].hight_)); 
                    width = rects[0].width_ + rects[1].width_ + rects[2].width_ + rects[3].width_;  
                    CheckAreaToAdd(target_rects,hight,width,min_area);
                }
            } 
        }
    }
    //create full permutation
    do{
        for(int i = 0; i < 2; i++){
            rects[0].Swap();
            for(int j = 0; j < 2; j++){
                rects[1].Swap();
                for(int m = 0; m < 2; m++){
                    rects[2].Swap();
                    for(int n = 0; n < 2; n++){
                        rects[3].Swap();
                        //type 2 
                        hight = Max(Max(rects[0].hight_,rects[1].hight_),rects[2].hight_)+rects[3].hight_; 
                        width = Max(rects[0].width_ + rects[1].width_ + rects[2].width_, rects[3].width_);  
                        CheckAreaToAdd(target_rects,hight,width,min_area);
                        //type 3
                        hight = Max(Max(rects[0].hight_+rects[2].hight_,rects[1].hight_+rects[2].hight_),rects[3].hight_);
                        width = Max(rects[0].width_+rects[1].width_,rects[2].width_)+rects[3].width_;
                        CheckAreaToAdd(target_rects,hight,width,min_area);
                        //type 4 and type 5
                        hight = Max(Max(rects[0].hight_,rects[1].hight_),rects[2].hight_+rects[3].hight_);
                        width = rects[0].width_+rects[1].width_+Max(rects[2].width_,rects[3].width_);
                        CheckAreaToAdd(target_rects,hight,width,min_area);
                        //type 6
                        hight = Max(rects[0].hight_+rects[2].hight_,rects[1].hight_+rects[3].hight_);
                        if(rects[2].hight_ >= rects[1].hight_+rects[3].hight_)
                            width = Max(rects[0].width_,Max(rects[1].width_+rects[2].width_,rects[2].width_+rects[3].width_));
                        else if(rects[2].hight_ > rects[3].hight_ && rects[2].hight_ < rects[1].hight_+rects[3].hight_)
                            width = Max(Max(rects[0].width_+rects[1].width_,rects[1].width_+rects[2].width_),rects[2].width_+rects[3].width_);
                        else if(rects[2].hight_ == rects[3].hight_)
                            width = Max(rects[0].width_+rects[1].width_,rects[2].width_+rects[3].width_);
                        else if(rects[2].hight_ < rects[3].hight_ && rects[0].hight_+rects[2].hight_ > rects[3].hight_)
                            width = Max(rects[0].width_+rects[1].width_,Max(rects[0].width_+rects[3].width_,rects[2].width_+rects[3].width_));
                        else if(rects[0].hight_+rects[2].hight_ <= rects[3].hight_)
                            width = Max(rects[1].width_,Max(rects[0].width_+rects[3].width_,rects[2].width_+rects[3].width_));
                        CheckAreaToAdd(target_rects,hight,width,min_area);
                    }
                } 
            }
        }
    }while(next_permutation(rects.begin(),rects.end(),CompareRect));//create full permutation
    // format the retangle 
    sort(target_rects.begin(),target_rects.end(),CompareRectHight);
    //output the result
    ofstream fout("packrec.out");
    fout<< min_area << endl;
    for(u_int i = 0; i < target_rects.size(); i++)
        fout<<target_rects[i].hight_ <<" "<< target_rects[i].width_<<endl;
    return 0;
}
