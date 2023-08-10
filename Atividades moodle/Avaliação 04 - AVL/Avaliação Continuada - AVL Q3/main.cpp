#include "avl.h"
#include <iostream>
#include <stack>
using namespace std;
int main(){
    system("chcp 65001 > null");
    avl_tree *t = new avl_tree;
    for(int i = 0; i <= 300; i++){
        t->add(i);
    }
    t->bshow();

}