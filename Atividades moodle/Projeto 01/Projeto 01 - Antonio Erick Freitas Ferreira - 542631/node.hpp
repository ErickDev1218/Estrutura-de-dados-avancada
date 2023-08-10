#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <string>
#include <vector>
#include "pessoa.hpp"

//Node de tipo generico pois a organização desta árvore
//vai variar entre string, Date e Cpf.
template <typename T, typename A>
class Node{
    public:
        int height;
        Node<T,A>* left;
        Node<T,A>* right;
        T key; //Criterio de organização
        A person; //Ponteiro pro objeto
        std::vector <A> sameT; //Caso exista mais de um objeto com o mesmo key

        //Construtor que inicializa um node com ambos os ponteiros como nullptr e
        //sua altura sempre com 1. Caso eu queria mudar esta inicialização padrão
        //devo passar os parametros na hora da criação deste node.
        //Atualmente os únicos parametros obrigatórios são: key e person.
        Node(T k, A p, Node<T,A>*l = nullptr, Node<T,A>*r = nullptr, int h = 1){
            key = k;
            person = p;
            left = l;
            right = r;
            height = h;
        }
        //Destrutor comentado para ser usado possivelmente na apresentação
        // ~Node(){
        //     std::cout << person->name << " deletada" << std::endl;
        // }
};
#endif