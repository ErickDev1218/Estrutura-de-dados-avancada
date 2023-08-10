#include <iostream>
#include "avl.h"
using namespace std;
void dobra(int& v){
    v *= 2;
}
int main() {
    avl_tree t;

    for(int i = 1; i <= 50; i++) {
        t.add(i);
    }

    t.bshow();

    for(int i = 1; i <= 40; i++)
        t.remove(i);

    t.bshow();

    for(int i = 41; i <= 47; i++)
        t.remove(i);

    t.bshow();

    t.access_keys_inorder(dobra);
}