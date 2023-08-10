#include <iostream>
#include <sstream>
#include <string>
#include <climits>
#include "Tree.h"

struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int k, Node *l = nullptr, Node *r = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
    }
};


Tree::Tree(std::string serial) {
    _root = nullptr;
    std::stringstream ss(serial);
    _serializeTree(ss, &_root);
}

void Tree::_serializeTree(std::stringstream& ss, Node **node) {
    std::string value;
    ss >> value;
    if(value == "#") // filho == nullptr
        return;
    int key = std::stoi(value);
    *node = new Node(key);
    _serializeTree(ss, &((*node)->left));
    _serializeTree(ss, &((*node)->right));
}

Tree::~Tree() {
    _clear(_root);
}

Node *Tree::_clear(Node *node) {
    if(node != nullptr) { // caso geral: vamos liberar essa arvore
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
    }
    return nullptr;
}

void Tree::inorder() {
    _inorder(_root);
}

void Tree::_inorder(Node *node) {
    if(node != nullptr) { // Caso Geral
        _inorder(node->left);
        std::cout << node->key << " ";
        _inorder(node->right);  
    }
}

void Tree::bshow(){
    _bshow(_root, "");
}

void Tree::_bshow(Node *node, std::string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->left, heranca + "l");
}


int Tree::sum_keys() { // TODO
    return _sum_keys(_root);
    
}

int Tree::_sum_keys(Node *node) { // TODO
    if(node == nullptr){ // caso base
        return 0;
    }
    return node->key + _sum_keys(node->left) + _sum_keys(node->right);
}

// Para fazer essa funcao, suponha que as arvores dos testes nunca serao vazias,
// assim, sempre havera um menor valor de chave a ser retornado
int Tree::min_key() { // TODO
    return _min_key(_root);
}


// Supoe que o ponteiro recebido sempre eh diferente de nullptr
int Tree::_min_key(Node *node) { // TODO
    if(node == nullptr){ // caso base
        return 0;
    }
    int count1 = 1000000; //so consegui fazer iniciando essas varias com valores altos;
    int count2 = 1000000;
    int actualValue = node->key;
    
    if(node->left != nullptr){ // pegando valor da esquerda
        count1 = _min_key(node->left);
    }
    if(node->right != nullptr){ // pegando valor da direita
        count2 = _min_key(node->right);
    }
    
    //agora comparo os 3 e devolvo o menor
    if(count1 < count2 && count1 < actualValue){
        return count1;
    }else if(count2 < count1 && count2 < actualValue){
        return count2;
    }
    return actualValue;
    
}

int Tree::total_internal_nodes() { // TODO
    return _total_internal_nodes(_root);
}
    
int Tree::_total_internal_nodes(Node *node) { // TODO
    if(node == nullptr){ //caso base
        return 0;
    }
    int count = 0;
    if(node->left != nullptr || node->right != nullptr){
        count = count + 1 + _total_internal_nodes(node->left) + _total_internal_nodes(node->right);
    }
    return count;
}

int Tree::um_filho() { // TODO
    return _um_filho(_root);
}

int Tree::_um_filho(Node *node) { // TODO
    if(node == nullptr){ // caso base
        return 0;
    }
    int count = 0;
    count += _um_filho(node->left); // descendo na arvore;
    count += _um_filho(node->right);
    
    
    if(node->left != nullptr && node->right == nullptr || node->left == nullptr && node->right != nullptr){
        count++;
    }
    return count;
    
}


