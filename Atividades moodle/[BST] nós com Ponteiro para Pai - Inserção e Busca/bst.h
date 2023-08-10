#ifndef BST_H
#define BST_H
#include <iostream>
#include <stack>
#include <string>
using namespace std;

/***********************************
 * Definicao do struct Node
 ***********************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/***********************************
 * Declaracao da classe
 ***********************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k); // ---> Implementar
    bool contains(int k); // ---> Implementar
    void inorderParent();
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *clear(Node *node); 
    Node *search(int k); // ---> Implementar
};

/************************************
 * Implementacao da classe
 ************************************/
// Constructor 1
BST::BST() {
    root = nullptr;
}

// Constructor 2
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
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

Node *BST::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = clear(root);
}

// Percorre os nos da arvore em ordem simetrica, imprimindo os pais
void BST::inorderParent() {
    stack<Node*> p; // Cria pilha do tipo Node* (ponteiro para Node)
    if(root != nullptr)
        p.push(root);
    while(!p.empty()) {
        Node *no = p.top();
        p.pop();
        if(no->parent != nullptr) cout << no->parent->key << " ";
        if(no->right != nullptr) p.push(no->right);
        if(no->left != nullptr) p.push(no->left);
    }
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    //TODO
    Node*aux = root;
    if(aux == nullptr){//caso arvore vazia
        Node* novo = new Node(k,nullptr,nullptr,nullptr);
        root = novo;
        return true;
    }
    while(true){ // caso nao vazia
        if(aux->key == k){
            return false;
        }
        if(aux->key < k){
            if(aux->right != nullptr){
                aux = aux->right;
            }else{
                break;
            }
        }else{
            if(aux->left !=nullptr){
                aux = aux->left;
            }else{
                break;
            }
        }
    }
    //aux está onde o nó deve ser adicionado
    if(aux->key < k){ // 3 < 4? vou à direita
        Node *novo = new Node(k,nullptr,nullptr,aux);
        aux->right = novo;
        return true;
    }else{ //3 > 4? vou à esquerda
        Node *novo = new Node(k,nullptr,nullptr,aux);
        aux->left = novo;
        return true;
    }
}

// Funcao privada 'search'
// Esta funcao devolve o ponteiro para o no que 
// contem a chave k se ela existir na arvore;
// caso contrario, devolve nullptr;
Node *BST::search(int k) {
    //TODO
    Node *aux = root;
    while(aux != nullptr){
        if(aux->key == k){
            return aux;
        }
        if(aux->key < k){
            aux = aux->right;
        }else{
            aux = aux->left;
        }
    }
    return aux;
    
}
//Depois que implementei que vi que nao pode ter nada recursivo zzzz
/*
bool contains_rec(Node* node, int key){
    if(node == nullptr){ //caso base
        return false;
    }
    if(node->key == key){
        return true;
    }
    if(node->key < key){ //3 < 4? vou à direita
        return contains_rec(node->right,key);
    }else{ // 3 > 4? vou à esquerda
        return contains_rec(node->left,key);
    }
}
*/
// Funcao publica 'contains'
// Esta funcao devolve 'true' se a arvore contem a chave k; 
// e devolve 'false' caso contrário.
bool BST::contains(int k) {
    //TODO
    Node* aux = root;
    while(aux != nullptr){
        if(aux->key == k){
            return true;
        }
        if(aux->key < k){
            aux = aux->right;
        }else{
            aux = aux->left;
        }
    }
    return false;
}

#endif 