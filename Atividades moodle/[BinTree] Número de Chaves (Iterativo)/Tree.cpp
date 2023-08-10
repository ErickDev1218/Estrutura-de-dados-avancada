#include <iostream>
#include <sstream>
#include <string>
#include <stack>
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

Tree::~Tree() {
    _root = _clear(_root);
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

Node *Tree::_clear(Node *node) {
    if(node != nullptr) { // caso geral: vamos liberar essa arvore
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
    }
    return nullptr;
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


int Tree::size() { // TODO
    return _size_iterativo(_root);
}

int Tree::_size_iterativo(Node *node) { // TODO
    //usar pilha. (estrutura LIFO)
    std::stack <Node*> pil;
    pil.push(node); //coloco a raiz na pilha
    int contador = 0; //contador do tamanho da árvore.
    while(!pil.empty()){//metodo empty me diz se a pilha está vazia ou nao devolvendo um bool
        Node *temp = pil.top(); //pegando o nó da pilha.
        pil.pop(); //removendo o nó da pilha (quebra de loop)
        if(temp != nullptr){
            contador++; //é um nó e precisa ser somado
            pil.push(temp->right); //primeiro passo o da direita pela estrutura LIFO
            pil.push(temp->left);//Esse nó será checado primeiro
        }
    }
    return contador;
    
}



