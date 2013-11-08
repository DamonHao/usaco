/*
ID: haolink1
PROG: sort3
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
//Main Idear
//The problem is quite easy, the key point is to consider all kinds of situation.
//We first calculate the number of 1,2,3,namely, counter1,counter2,counter3
//So, when the sequence is in non-decreasing order, number 1 shoud be in place(start from 0) 
//[0,counter1-1],2 in [counter1,counter1+counter2-1] and 3 in [counter1+counter2,sequence_lenght-1]
//Then we can count then number in wrong place and use the min swap step to put them in order.
int main(){
    ifstream fin("sort3.in");
    short len = 0;
    fin >> len;
    short* numbers = new short[len];
    for(short i = 0; i < len; i++){
        fin >> numbers[i];
    }
    //calculate the number of 1,2,3 and store them in counter[0],counter[1],counter[2] respectively
    short counter[3] = {0};
    for(short i = 0; i < len; i++){
       counter[numbers[i]-1]++; 
    }
//    for(short i = 0; i < 3; i++){
//        cout<<counter[i]<<endl;
//    }
    //caltulate the number in the wrong place. 
    //Eg: number 2, and 3 shoudn't appear in the palce that's lower then counter[0]
    short num_2_in_1 = 0;
    short num_3_in_1 = 0;
    for(short i = 0; i< counter[0]; i++){
        if(numbers[i] == 2)
            num_2_in_1++;
        if(numbers[i] == 3)
            num_3_in_1++;
    }
    short num_1_in_2 = 0;
    short num_3_in_2 = 0;
    for(short i = counter[0]; i < counter[0]+counter[1]; i++){
        if(numbers[i] == 1)
            num_1_in_2++;
        if(numbers[i] == 3)
            num_3_in_2++;
    }
    short num_1_in_3 = 0;
    for(short i =counter[0]+counter[1]; i < len; i++){
        if(numbers[i] == 1)
            num_1_in_3++;
    }
//    cout<<num_2_in_1<<" "<<num_3_in_1<<" "<<num_1_in_2<<" "<<num_3_in_2<<" "<<num_1_in_3<<endl;
    //calculate the swap times we need to make the sequence in order.
    short swap_num = 0;
    if(num_2_in_1 > 0){
        if(num_2_in_1 <=  num_1_in_2){
            swap_num += num_2_in_1;
            num_1_in_2 -= num_2_in_1;
            num_2_in_1 = 0;
        }else{
            swap_num += num_1_in_2;
            num_2_in_1 -= num_1_in_2;
            num_1_in_2 = 0;
        }
        if(num_2_in_1 > 0){
            swap_num += 2*num_2_in_1;
            num_1_in_3 -= num_2_in_1;
            num_3_in_2 -= num_2_in_1;
            num_2_in_1 = 0;
        }
    }
    if(num_3_in_1 > 0){
        if(num_3_in_1 <= num_1_in_3){
            swap_num += num_3_in_1;
            num_1_in_3 -= num_3_in_1;
            num_3_in_1 = 0;
        }else{
            swap_num += num_1_in_3;
            num_3_in_1 -= num_1_in_3;
            num_1_in_3 = 0;
        }
        if(num_3_in_1 > 0){
            swap_num += 2*num_3_in_1;
            num_1_in_2 -= num_3_in_1;
            //num_2_in_3 -= num_3_in_1;
            num_3_in_1 = 0;
        }
    }
    if(num_3_in_2 > 0){
        swap_num += num_3_in_2;  
    }
    ofstream fout("sort3.out");
    fout<<swap_num<<endl;
    delete[] numbers;
    return 0;
}
