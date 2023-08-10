#include "avl.h"
#include <iostream>
using namespace std;
int main(){
    system("chcp 65001 > null");
    avl_tree *t = new avl_tree;
    for(int i = 0; i <= 10; i++){
        t->add(i);
    }
    t->bshow();

    cout << endl << endl;

    avl_tree *t2 = new avl_tree;
    for(int i = 0; i <= 20; i++){
        t2->add(i);
    }
    t2->bshow();
    cout << endl << endl;

    avl_tree *t3 = new avl_tree;
    t3->junc(t,t2);
    t3->bshow();
    cout << endl;

}