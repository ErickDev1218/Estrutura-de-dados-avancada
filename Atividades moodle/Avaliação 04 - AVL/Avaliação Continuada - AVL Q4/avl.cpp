#include <iostream>
#include <vector>
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
    root = add(root,key);
}

Node* avl_tree::add(Node *p, int key) {
    if(p == nullptr){
        return new Node(key);
    }
    if(p->key == key){
        //faz nada.
        return p;
    }else if(p->key < key){
        p->right = add(p->right,key);
    }else{
        p->left = add(p->left,key);
    }
    //Hora de balancear a arvore.
    p = fixup_node(p,key);
    return p;
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
        p = rightRotation(p);
    }
    //Caso 1(b)
    else if(bal < -1 && key > p->left->key){
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    //Caso 2(a)
    else if(bal > 1 && key > p->right->key){
        p = leftRotation(p);
    }
    //Caso 2(b)
    else if(bal > 1 && key < p->right->key){
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
//Funcao final recursiva que cria a arvore.
Node* avl_tree::createOrd(Node *raiz,int v[], int p, int q){
    if(p > q){
        return nullptr;
    }
    raiz = new Node(v[(p+q)/2]);
    raiz->left = createOrd(raiz->left,v,p,(p+q)/2-1);
    raiz->right = createOrd(raiz->right,v,(p+q)/2+1,q);
    raiz = fixup_node(raiz,(p+q/2));
    return raiz;
}

//Funções para receber duas árvores e criar uma terceira
void avl_tree::junc(avl_tree *arv1,avl_tree *arv2){
    vector<int> final = junction(arv1,arv2);
    int v[final.size()];
    int i = 0;
    for(i = 0; i < final.size(); i++){
        v[i] = final [i];
    }
    root = createOrd(root,v,0,i-1);
}
//Funcao que pega todos os valores de uma árvore e joga
//para dentro de um vector
vector<int> avl_tree::caughtValue(avl_tree *arv){
    //Caso a arvore seja vazia.
    vector<int> final;
    if(arv->root == nullptr){
        return final;
    }
    //Caso a árvore tenha N nós.
    stack <Node*> pil;
    Node *aux = arv->root;
    //Busca iterativa em ordem simetrica para ter
    //o vector em ordem (da árvore).
    //Função com complexidade O(n)
    while(!pil.empty() || aux != nullptr){
        while(aux != nullptr){
            pil.push(aux);
            aux = aux->left;
        }
        aux = pil.top();
        pil.pop();
        final.push_back(aux->key);
        aux = aux->right;
    }
    return final;
}
//Funcao que faz o terceiro vetor ordenado
vector<int> avl_tree::junction(avl_tree *arv1,avl_tree *arv2){
    vector <int> firstTree = caughtValue(arv1);
    vector <int> secondTree = caughtValue(arv2);
    int i = 0; //primeiro vector
    int k = 0; //segundo vector
    vector<int> final;

    while(i < firstTree.size() && k < secondTree.size()){
        if(firstTree[i] < secondTree[k]){
            final.push_back(firstTree[i]);
            i++;
        }else if(secondTree[k] < firstTree[i]){
            final.push_back(secondTree[k]);
            k++;
        }else{
            final.push_back(firstTree[i]);
            i++;
            k++;
        }
    }
    if(i < firstTree.size() && k == secondTree.size()){ //Ainda há elementos do primeiro vector para entrar
        while(i < firstTree.size()){
            final.push_back(firstTree[i]);
            i++;
        }
    }else if(k < secondTree.size() && i == firstTree.size()){//há elementos do segundo vetor para entrar
        while(k < secondTree.size()){
            final.push_back(secondTree[k]);
            k++;
        }
    }
    // for(int i = 0; i < firstTree.size(); i++){
    //     cout << firstTree[i] << " ";
    // }
    // cout << endl;
    // for(int i = 0; i < secondTree.size(); i++){
    //     cout << secondTree[i] << " ";
    // }
    // cout << endl;
    // for(int i = 0; i < final.size(); i++){
    //     cout << final[i] << " ";
    // }
    // cout << endl;
    return final;
}