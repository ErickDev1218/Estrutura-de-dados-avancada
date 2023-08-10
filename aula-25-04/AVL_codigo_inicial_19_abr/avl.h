#ifndef AVL_H
#define AVL_H
#include <string>
#include "node.h"
#include "dynamic_set.h"

class avl_tree : public dynamic_set {
public:
    avl_tree() = default;
    avl_tree(const avl_tree& t); //Construtor de cópia OK

    avl_tree& operator=(const avl_tree& t); // OK
    void bshow() const;
    ~avl_tree();

    virtual void access_keys_inorder(void (*f)(int& key)) override;   // O(n) OK
    virtual void keys_as_vector(std::vector<int>& v) const override;  // O(n) 

    virtual void add(int key) override;                               // O(lg n) OK
    virtual void remove(int key) override;                            // O(lg n) OK
    virtual int size() const override;                                // O(n) OK

    virtual bool contains(int key) const override;                    // O(lg n)
    virtual int minimum() const override;                             // O(lg n)
    virtual int maximum() const override;                             // O(lg n)
    virtual int successor(int key) const override;                    // O(lg n)
    virtual int predecessor(int key) const override;                  // O(lg n)
    virtual bool empty() const override;                              // O(1)
    virtual void clear() override;  
    
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
    Node* remove(Node *node, int key); 
    Node* remove_successor(Node *root, Node *node);
    Node* fixup_deletion(Node *node);
};

#endif