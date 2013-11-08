/*
ID: haolink1
PROG: frac1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // std::sort
using namespace std;

class Fraction{
public:
    short up_num_;
    short down_num_;
    Fraction(short up_num,short down_num):
        up_num_(up_num),down_num_(down_num){}
};

bool RelativelyPrime(short num1,short num2);
bool CompareValue(Fraction first, Fraction second);

int main(){
    ifstream fin("frac1.in");
    short num = 0;
    fin >> num;
    vector<Fraction> numbers;
    for(short i = 1; i < num; i++){
        for(short j = i+1; j <= num; j++){
            if(RelativelyPrime(i,j))
                numbers.push_back(Fraction(i,j));
        }
    }
    sort(numbers.begin(),numbers.end(),CompareValue);
    ofstream fout("frac1.out");
    fout<<"0/1"<<endl;
    int numbers_size = numbers.size();
    for(int i =0; i < numbers_size; i++)
        fout << numbers[i].up_num_<<'/'<<numbers[i].down_num_<<endl;
    fout<<"1/1"<<endl;
    return 0;
}
/*
bool RelativelyPrime(short num1,short num2){
    short min = num1 <= num2?num1:num2; 
    for(short i = 2; i <= min; i++){
        if(num1%i == 0 && num2%i == 0)
            return false;
    }
    return true;
}
*/
bool RelativelyPrime(short a, short b){
   int r = a % b;
   while(r != 0){
       a = b;
       b = r;
       r = a % b;
   }
   return(b == 1);
}
/*
bool CompareValue(Fraction first, Fraction second){
   if(float(first.up_num_)/first.down_num_ < float(second.up_num_)/second.down_num_) 
       return true;
   else return false;
}
*/
bool CompareValue(Fraction first, Fraction second){
     return first.up_num_*second.down_num_ - second.up_num_*first.down_num_ < 0;
}
