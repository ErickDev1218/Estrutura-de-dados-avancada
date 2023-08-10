#ifndef AVL_H
#define AVL_H
#include <vector>
#include <stack>
#include "node.h"
#include "string"

class avl_tree{
public:
    avl_tree() = default;
    avl_tree(const avl_tree& t) = delete;
    avl_tree& operator=(const avl_tree& t) = delete;
    void add(int key);
    void bshow() const;
    void clear();
    ~avl_tree();
    void junc(avl_tree *arv1,avl_tree *arv2);
    
private:
    Node *root {nullptr};
    int height(Node *node);
    int balance(Node *node);
    Node* rightRotation(Node *p);
    Node* leftRotation(Node *p);
    Node* add(Node *p, int key);
    Node* fixup_node(Node *p, int key);
    void bshow(Node *node, std::string heranca) const;
    Node* clear(Node *node);
    //funções para receber duas árvores e criar a terceira.
    std::vector<int> caughtValue(avl_tree *arv);
    std::vector<int> junction(avl_tree *arv1,avl_tree *arv2);
    Node* createOrd(Node*raiz,int v[],int p, int q);
};

#endif