/*
ID: haolink1
PROG: crypt1
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
bool IsInSet(int digit, int digit_num, int* digits){
    for(int i = 0; i < digit_num; i++){
        if(digit == digits[i])
            return true;
    }
    return false;
}

bool IsValueValid(int value, int digit_num, int* digits){
    vector<int> value_digit;
    while(value/10 != 0){
        value_digit.push_back(value % 10);
        value /= 10;
    }
    value_digit.push_back(value);
    for(int i = 0; i < value_digit.size(); i++){
        if(!IsInSet(value_digit[i],digit_num,digits)) 
            return false;
    }
    return true;
}

int main(){
    ifstream fin("crypt1.in");
    int digit_num = 0;
    fin >> digit_num;
    int* digits = new int[digit_num];
    for(int i = 0; i < digit_num; i++){
        fin>>digits[i];
    }
    int total_solution = 0;
    vector<int> partial_products;
    //traverse all possible value of the top number
    for(int i = 0; i < digit_num; i++){
        for(int j = 0; j < digit_num; j++){
            for(int k = 0; k < digit_num; k++){
                //traverse the digit in second number
                for(int m = 0; m < digit_num; m++){
                    int partial_product = (digits[i]*100+digits[j]*10+digits[k])*digits[m];
                    //collect the valid partial product
                    if(partial_product < 1000 && IsValueValid(partial_product,digit_num,digits))
                            partial_products.push_back(partial_product);
                }
                //traverse all the valid partial product
                int product_num = partial_products.size();
                for(int n = 0; n < product_num; n++){
                    for(int m = 0; m < product_num; m++){
                        int sum = partial_products[n]*10 + partial_products[m];
                        if(sum < 10000 && IsValueValid(sum,digit_num,digits))
                           total_solution++; 
                    }
                }
                partial_products.clear();
            }
        } 
    }
    ofstream fout("crypt1.out");
    fout<<total_solution<<endl;
    delete[] digits;
    return 0;
}
