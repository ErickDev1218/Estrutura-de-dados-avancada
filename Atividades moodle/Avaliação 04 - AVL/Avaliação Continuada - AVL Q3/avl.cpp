#include <iostream>
#include <stack>
#include "node.h"
#include "avl.h"
using namespace std;
//Retorna a altura do nó
//Se nó vazio retorna 0
//Senao retorna a altura do no (height)
int avl_tree::height(Node *node) {
    return !node ? 0 : node->height;
}

int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;

    //recalcular as alturas de P e de U, já que foram mudados de posição.
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
}

Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;

    //recalcular as alturas de P e de U, já que foram mudados de posição.
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
}

void avl_tree::add(int key) {
    add(root,key);
}

void avl_tree::add(Node *p, int key) {
    Node *walker = p; //walker ponta pra p.
    Node *novo = new Node(key);
    if(walker == nullptr){ //Caso seja ainda seja uma árvore vazia
        root = novo;
        return;
    }
    stack <Node*> pil;
    //Há pelo menos um nó nessa árvore
    Node *prevWalker = nullptr;
    while(walker != nullptr){
        if(walker->key < key){
            pil.push(walker);
            prevWalker = walker;
            walker = walker->right;
        }else{
            prevWalker = walker;
            pil.push(walker);
            walker = walker->left;
        }
    }
    //Walker agora está apontando para nullptr
    //o caminho que ele percorreu está todo na pilha
    //e prevWalker está onde o nó deve ser inserido.

    //Fazendo com o que o ultimo nó aponte para o nó recém criado
    if(prevWalker->key < key){
        prevWalker->right = novo;
    }else{
        prevWalker->left = novo;
    }
    //pil.push(prevWalker);
    //Agora que o nó foi criado e já adicionado corretamente na árvore
    //o que resta é corrigir as alturas e manter a propriedade AVL.
    while(!pil.empty()){ //Enquanto a pilha nao estiver vazia.
        Node *aux = pil.top();
        pil.pop(); // Retirei o primeiro nó da pilha pois aux já o tem.
        if(!pil.empty()){
            if(pil.top()->key < key){
                pil.top()->right = fixup_node(aux,key);
            }else if(pil.top()->key > key){
                pil.top()->left = fixup_node(aux,key);
            }
        }else{
            root = fixup_node(aux,key);
        }
        //cout << "cheguei aqui" << endl;
    }
}

Node* avl_tree::fixup_node(Node *p, int key) {
    //Começo recalculando a altura do nó.
    p->height = 1 + max(height(p->left),height(p->right));
    //Agora, olho o fator de balanceamento desse nó.
    int bal = balance(p);

    //Agora inicia as tomadas de decisoes.
    //Se não estiver desbalanceado.
    if(bal >= -1 && bal <= 1){
        return p;
    }
    //Caso 1(a)
    if(bal < -1 && key < p->left->key){
        return rightRotation(p);
    }
    //Caso 1(b)
    else if(bal < -1 && key > p->left->key){
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    //Caso 2(a)
    else if(bal > 1 && key > p->right->key){
        return leftRotation(p);
    }
    //Caso 2(b)
    else if(bal > 1 && key < p->right->key){
        p->right = rightRotation(p->right);
        return leftRotation(p);
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