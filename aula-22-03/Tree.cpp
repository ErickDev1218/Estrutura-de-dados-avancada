#include "Tree.h"

using namespace std;

/********************************************************
 * Funcoes recursivas auxiliares
*/
void preorder_rec(Node* node) {
    if(node != nullptr) { // Caso geral: arvore nao vazia
        std::cout << node->key << " ";
        preorder_rec(node->left);
        preorder_rec(node->right);
    }
}

void posorder_rec(Node* node) {
    if(node != nullptr) { // Caso geral: arvore nao vazia
        posorder_rec(node->left);
        posorder_rec(node->right);
        std::cout << node->key << " ";
    }
}

void inorder_rec(Node* node) {
    if(node != nullptr) { // Caso geral: arvore nao vazia
        inorder_rec(node->left);
        std::cout << node->key << " ";
        inorder_rec(node->right);
    }
}

bool contain_rec(Node *node, int key){
    if(node == nullptr){ // caso base
        return false;
    }
    if(node->key == key){
        return true;
    }
    return contain_rec(node->left,key) || contain_rec(node->right,key);
    
    
}

Node* clear_rec(Node *node){
    if(node == nullptr){ //caso base
        return nullptr;
    }
    node->left = clear_rec(node->left);
    node->right = clear_rec(node->right);

    delete node;
    return nullptr;
}

int size_rec(Node *node){
    if(node == nullptr){
        return 0;
    }
    return 1 + size_rec(node->left) + size_rec(node->right);
}

/*********************************************************
 * Implementacao das funcoes-membro da classe Tree
*/
void Tree::preorder() {
    preorder_rec(root);
}

void Tree::inorder() {
    inorder_rec(root);
}

void Tree::posorder() {
    posorder_rec(root);
}

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree(){
    clear();
}

// Cria um novo no com chave key e seus
// filhos serao as raizes de tl e tr.
// tl e tr serao arvores vazias ao final dessa funcao
Tree::Tree(int key, Tree& tl, Tree& tr) 
{
    root = new Node(key, tl.root, tr.root); // chama o construtor do struct Node
    tl.root = nullptr; // faz a arvore tl ficar vazia
    tr.root = nullptr; // faz a arvore tr ficar vazia
}

bool Tree::empty(){
    return root == nullptr;
}

bool Tree::contain(int key){
    return contain_rec(root,key);
}

void Tree::clear(){
   root = clear_rec(root);
}

int Tree::size(){
    return size_rec(root);
}