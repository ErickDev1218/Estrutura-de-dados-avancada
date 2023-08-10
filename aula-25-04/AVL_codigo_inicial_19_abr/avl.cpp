#include <iostream>
#include "node.h"
#include "avl.h"
using namespace std;

// retorna a altura do nó.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que está no campo height
int avl_tree::height(Node *node) {
    return (node == nullptr) ? 0 : node->height;
}

int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// função pública que recebe uma chave e a insere
// somente se ela não for repetida
void avl_tree::add(int key) {
    root = add(root, key);
}

// função recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na tree se e somente se 
// ela nao for repetida. Claro, tem que deixar AVL novamente
Node* avl_tree::add(Node *p, int key) {
    if(p == nullptr)
        return new Node(key);
    if(key == p->key) 
        return p;
    if(key < p->key)
        p->left = add(p->left, key);
    else 
        p->right = add(p->right, key);
    
    p = fixup_node(p, key);

    return p;
}

Node* avl_tree::fixup_node(Node *p, int key) {
    // recalcula a altura de p
    p->height = 1 + max(height(p->left),height(p->right));

    // calcula o balanço do p
    int bal = balance(p);

    if(bal >= -1 && bal <= 1) {
        return p;
    }

    if(bal < -1 && key < p->left->key) {
        p = rightRotation(p);
    }
    else if(bal < -1 && key > p->left->key) {
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    else if(bal > 1 && key > p->right->key) {
        p = leftRotation(p);
    }
    else if(bal > 1 && key < p->right->key) {
        p->right = rightRotation(p->right);
        p = leftRotation(p);
    }
    return p;
}

void avl_tree::clear() {
    root = clear(root);
}

Node *avl_tree::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

avl_tree::~avl_tree() {
    clear();
}

void avl_tree::bshow() const {
    bshow(root, "");
}

void avl_tree::bshow(Node *node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
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
        bshow(node->left, heranca + "l");
}

void avl_tree::remove(int key) {
    root = remove(root, key);
}

Node* avl_tree::remove(Node *node, int key) {
    if(node == nullptr) // node nao encontrado
        return nullptr; /*L\pauseL*/
    if(key < node->key) 
        node->left = remove(node->left, key);
    else if(key > node->key)
        node->right = remove(node->right, key); /*L\pauseL*/
    // encontramos no node
    else if(node->right == nullptr) { // sem filho direito
        Node *child = node->left;
        delete node;
        return child;
    }
    else // tem filho direito: troca pelo sucessor
        node->right = remove_successor(node, node->right); /*L\pauseL*/
    
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node); 
    return node;
}

Node* avl_tree::remove_successor(Node *root, Node *node) {
    if(node->left != nullptr)
        node->left = remove_successor(root, node->left);
    else {
        root->key = node->key;
        Node *aux = node->right;
        delete node;
        return aux;
    }
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node);
    return node;
}

Node* avl_tree::fixup_deletion(Node *node) {
    node->height = 1 + max(height(node->left),height(node->right));

    int bal = balance(node);

    // node pode estar desregulado, ha 4 casos a considerar
    if(bal > 1 && balance(node->right) >= 0) {
        return leftRotation(node);
    }
    else if(bal > 1 && balance(node->right) < 0) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    else if(bal < -1 && balance(node->left) <= 0) {
        return rightRotation(node);
    }
    else if(bal < -1 && balance(node->left) > 0) { 
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    return node;
}
//Recebe um ponteiro para a raiz de uma árvore
//e retorna o clone dessa árvore
Node* clone_rec(Node *node){
    if(node == nullptr){
        return nullptr;
    }

    Node* aux = new Node(node->key);
    aux->left = clone_rec(node->left);
    aux->right = clone_rec(node->right);

    return aux;
}
//Construtor de copia, recebe uma avl_tree e cria um clone
//dessa árvore e faz a minha árvore ser esse clone
avl_tree::avl_tree(const avl_tree& t){
    this->root = clone_rec(t.root);
}

avl_tree& avl_tree::operator=(const avl_tree& t){
    if(this != &t){ //Se a minha árvore for diferente da árvore passada. t = t.
        clear();
        this->root = clone_rec(t.root);
    }
    return *this;
}

void inorder_rec(Node *node,void (*f)(int& key)){
    if(!node){
        inorder_rec(node->left,f);
        f(node->key);
        inorder_rec(node->right,f);

    }
}

void avl_tree::access_keys_inorder(void (*f)(int& key)){
    inorder_rec(root,f);
}
//Recebe uma raiz e um vetor
//Percorre em ordem simetrica preenchendo o vetor.
void inorder_rec(Node* node,std::vector<int>& v ){
    if(node != nullptr){
        inorder_rec(node->left,v);
        v.push_back(node->key);
        inorder_rec(node->right,v);
    }
}

void avl_tree::keys_as_vector(std::vector<int>& v) const{
    inorder_rec(root,v);
} 