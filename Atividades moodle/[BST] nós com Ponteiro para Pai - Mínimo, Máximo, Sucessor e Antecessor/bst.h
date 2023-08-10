#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <climits>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
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

/************************
 * Declaracao da classe
 ************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    int minimum();           // ---> Implementar
    int maximum();           // ---> Implementar
    int predecessor(int k);  // ---> Implementar
    int successor(int k);    // ---> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *minimum(Node *node);       // ---> Implementar
    Node *maximum(Node *node);       // ---> Implementar
    Node *successor(Node *node);     // ---> Implementar
    Node *predecessor(Node *node);     // ---> Implementar
    Node *clear(Node *node);
    Node *search(int k);
};

/*****************************
 * Implementacao da classe
 *****************************/
// Construtor 
BST::BST() {
    root = nullptr;
}

// Construtor 
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

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    //TODO: adicione aqui o codigo feito no exercicio anterior
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
    //TODO: adicione aqui o codigo feito no exercicio anterior
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

// Funcao publica (obrigatoriamente iterativa)
// Devolve o menor valor de chave da arvore.
int BST::minimum() {
    // TODO
    if(minimum(root) != nullptr){
        return minimum(root)->key;
    }else{
        throw std::runtime_error ("Arvore vazia");
    }
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a menor chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::minimum(Node *node) {
    // TODO
    if(node == nullptr){
        return nullptr;
    }
    Node *aux = node;
    while(aux->left != nullptr){
        aux = aux->left;
    }
    return aux;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o maior valor de chave da arvore
int BST::maximum() {
    // TODO
    if(maximum(root) != nullptr){
        return maximum(root)->key;
    }else{
        throw std::runtime_error ("Arvore vazia");
    }
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::maximum(Node *node) {
    // TODO
    if(node == nullptr){
        return nullptr;
    }

    Node *aux = node;
    while(aux->right != nullptr){
        aux = aux->right;
    }
    return aux;
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MAX se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem sucessor
// (2) caso contrario, devolve o valor inteiro da 
// chave sucessora de k quando esta existe
int BST::successor(int k) {
    // TODO
    Node* test = search(k);
    if(test != nullptr){
        Node *suc = successor(test);
        if(suc != nullptr){
            return suc->key;
        }
    }
    return INT_MAX;

}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem sucessor; ou
// (2) caso contrario, devolve o ponteiro para o no sucessor de node.
Node *BST::successor(Node *node) {
    // TODO
    if(node->right != nullptr){ //Se existe subarvore a direita, então o sucessor é o minimo de lá.
        return minimum(node->right);
    }
    //Caso não exista, seu sucessor é o primeiro nó a direita na subida.
    Node*walker = root;
    Node*succ = nullptr;
    //succ será o nó que pode ser um sucessor
    while(walker != node){
        if(walker->key < node->key){
            walker = walker->right;
        }else{
            succ = walker;
            walker = walker->left;
        }
    }
    if(succ != nullptr && succ->key > node->key){ //A segunda parte parece redundante, mas sinto que é bom ter.
        return succ;
    }else{
        return nullptr;
    }

}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MIN se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem antecessor;
// (2) caso contrario, devolve o valor inteiro da chave 
// antecessora de k quando esta existe.
int BST::predecessor(int k) {
    // TODO
    Node* test = search(k);
    if(test != nullptr){
        Node *pred = predecessor(test);
        if(pred != nullptr){
            return pred->key;
        }
    }
    return INT_MIN;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem antecessor; ou
// (2) caso contrario, devolve o ponteiro para o no antecessor de node.
Node *BST::predecessor(Node *node) {
    // TODO
    if(node->left != nullptr){ //Existe subarvore a esquerda e o predecessor será o máximo da mesma.
        return maximum(node->left);
    }
    //O predecessor será o primeiro o primeiro nó a esquerda na subida
    Node*walker = root;
    Node*pred = nullptr;
    while(walker != node){
        if(walker->key > node->key){
            walker = walker->left;
        }else{
            pred = walker;
            walker = walker->right;
        }
    }

    if(pred != nullptr && pred->key < node->key){
        return pred;
    }else{
        return nullptr;
    }
}

#endif 