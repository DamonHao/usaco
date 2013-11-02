/*
ID: haolink1
PROG: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <list>
using namespace std;

class Milk{
public:
    int price_;
    int amount_;
    Milk(int price, int amount):
        price_(price),amount_(amount){}
    Milk(const Milk& milk){
        price_ = milk.price_;
        amount_ = milk.amount_;
    }
    ~Milk(){}
};

bool ComparePrice(const Milk& milk1,const Milk& milk2){
    if(milk1.price_ <= milk2.price_)
        return true;
    return false;
}

int main(){
    ifstream fin("milk.in");
    int demand = 0;
    int farmer_num = 0;
    fin >> demand;
    fin >> farmer_num;
    list<Milk> milks;
    int price = 0;
    int amount = 0;
    for(int i = 0; i < farmer_num; i++){
        fin >> price;fin >> amount;
        Milk milk(price,amount);
        milks.push_back(milk);
    }
    // sort the milk price in ascending order
    milks.sort(ComparePrice);
    int cost = 0;
    for(list<Milk>::iterator it = milks.begin(); it != milks.end(); it++){ 
        int remainder =  demand - it->amount_;
        if(remainder > 0){
            cost += it->price_ * it->amount_; 
            demand = remainder;
        }else if(remainder == 0){
            cost += it->price_ * it->amount_; 
            break;
        }else{
            cost += it->price_ * demand;
            break;
        }
    }
    ofstream fout("milk.out");
    fout << cost <<endl;
}
