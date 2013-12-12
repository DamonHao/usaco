/*
Main idea:
Choose node in pre order, and then use in order info to jude left or right.Througt this we can 
build a tree. Finally, we wall through the tree in post order to get answer;
From this problem, we can infer that we can build a tree by two of the tree order and its building
way is similar to the above, choose node in one tree order and jude left or right by anoter tree order ;
*/
/*
Executing...
   Test 1: TEST OK [0.000 secs, 3504 KB]
   Test 2: TEST OK [0.000 secs, 3504 KB]
   Test 3: TEST OK [0.000 secs, 3504 KB]
   Test 4: TEST OK [0.000 secs, 3504 KB]
   Test 5: TEST OK [0.000 secs, 3504 KB]
   Test 6: TEST OK [0.000 secs, 3504 KB]
   Test 7: TEST OK [0.000 secs, 3504 KB]
   Test 8: TEST OK [0.000 secs, 3504 KB]
   Test 9: TEST OK [0.000 secs, 3504 KB]

All tests OK.
*/

/*
ID: haolink1
PROG: heritage
LANG: C++
*/

//#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Node{
public:
    char key_;
    Node* left_; 
    Node* right_;
    Node(char key){key_ = key; left_ = NULL; right_ = NULL;}
};
ifstream fin("heritage.in");
ofstream cout("heritage.out");
int index[26];

void BuildTree(Node* cur, Node* new_one){
    if(index[cur->key_-'A'] > index[new_one->key_-'A']){
        if(cur->left_ == NULL)
            cur->left_ = new_one;
        else
            BuildTree(cur->left_,new_one);
    }else{
        if(cur->right_ == NULL)
            cur->right_ = new_one;
        else
            BuildTree(cur->right_,new_one);
    }
}

void PostOrder(Node* cur){
    if(cur->left_ != NULL)
        PostOrder(cur->left_);
    if(cur->right_ != NULL)
        PostOrder(cur->right_);
    cout << cur->key_;
}
//Note we can only delete node in post order;
void PostOrderDelete(Node* cur){
    if(cur == NULL) return;
    if(cur->left_ != NULL)
        PostOrder(cur->left_);
    if(cur->right_ != NULL)
        PostOrder(cur->right_);
    delete cur;
}

int main(){
    string in_str,pre_str;
    fin >> in_str >> pre_str;
    int len = in_str.length();
    for(int i = 0; i < len; i++){
        index[in_str[i] - 'A'] = i+1;
    }
    Node root(pre_str[0]);
    //Chose node in post order;
    for(int i = 1; i < len; i++){
        BuildTree(&root,new Node(pre_str[i]));
    }
    PostOrder(&root);
    cout << endl;
    PostOrderDelete(root.left_);
    PostOrderDelete(root.right_);
    return 0;
}
