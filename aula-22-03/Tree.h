#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "Node.h"

class Tree {
private:
    Node *root; // ponteiro para a raiz da arvore

public:
    // Construtor: cria arvore vazia
    Tree(); 
    //destrutor
    ~Tree();
    //construtor de cópia
    Tree(const Tree& t) = delete;

    // Construtor: cria uma arvore com chave key
    // e cujos filhos serao as raizes das arvores tl e tr.
    // tl e tr serao arvores vazias ao final dessa funcao
    Tree(int key, Tree& tl, Tree& tr); 

    // funcoes que executam percursos especificos na arvore
    // imprimindo o valor das chaves na tela
    void preorder();
    void inorder();
    void posorder();
    //retorna true se a arvore vazia e false caso contrario
    bool empty();
    //retorna true se o key estiver na arvore e false caso contrario
    bool contain(int key);
    //funcao que deixa a arvore vazia
    void clear();
    //retorna o numero de nós da arvore
    int size();
};

#endif 
