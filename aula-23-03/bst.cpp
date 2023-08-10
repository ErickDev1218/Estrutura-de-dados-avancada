#include "bst.h"
using namespace std;

Node* BST::search(Node* node, int key){
    if(node == nullptr){
        return nullptr;
    }
    if(node->key == key){
        return node;
    }
    if(node->key < key){
        return search(node->right,key);
    }else{
        return search(node->left,key);
    }
}

bool BST::contains(int key){
    return search(root,key) != nullptr;
}