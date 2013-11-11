/*
ID: haolink1
PROG: runround
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned long u_long;
typedef long long l_long;

bool visited_digit[10] = {false}; 
short digits[20] = {0};

//Main Idea
//First check whether the digits are unique
//then check the runround property;
int main(){
    ifstream fin("runround.in");
    u_long begin;
    fin >> begin;
    //cout << sizeof(long) <<" "<<sizeof(long long)<<endl;
    l_long max = u_long(-1) ;
    for(l_long i = begin + 1; i <= max; i++){
        short remainder = 0;
        bool digit_unique = true;
        short digit_counter = 0;
        l_long cur_value = i;
        //Check digit unique;
        while(cur_value > 0){
            remainder = cur_value % 10;
            if(visited_digit[remainder] == true){
                digit_unique = false;
                break;
            }else{ 
                visited_digit[remainder] = true;
                digits[digit_counter++] = remainder;
            }
            cur_value /= 10;
        }
        if(digit_unique == true){
            //Reset 
            for(short i = 0; i < 10; i++){
                visited_digit[i] = false;
            }
            //Check runround property;
            bool is_valid = true;
            short digit_num = digit_counter;
            //Note -5 % 10 = -5; So in order to make sure the modulus is positive we use 9 * digit_num;
            short cur_index = (digit_num - 1 -digits[digit_num-1] + 9 * digit_num)%digit_num;
            while(digit_counter > 0){
                if(visited_digit[cur_index] == false){
                    visited_digit[cur_index] = true;
                    cur_index = (cur_index - digits[cur_index] + 9 * digit_num)%digit_num;
                    digit_counter--;
                }else{
                    is_valid = false;
                    break;
                }
                //The index "digit_num -1" should be visited last;
                if(cur_index == (digit_num -1) && digit_counter != 1){
                    is_valid = false;
                    break;
                }
            }
            if(is_valid == true){
                ofstream fout("runround.out");
                for(short j = digit_num - 1; j >=0;j--){
                    fout<<digits[j];
                }    
                fout<<endl;
                return 0;
            }
        }
        //Reset 
        for(short i = 0; i < 10; i++){
            visited_digit[i] = false;
        }
    }
    return 0;
}
