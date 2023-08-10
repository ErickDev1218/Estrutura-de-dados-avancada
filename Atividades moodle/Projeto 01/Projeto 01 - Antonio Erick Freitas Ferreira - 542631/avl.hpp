#ifndef AVL_HPP
#define AVL_HPP
#include "node.hpp"
#include "pessoa.hpp"
#include "date.hpp"
#include "cpf.hpp"
#include <string>
using namespace std;

template <typename T, typename A>
class avl{
    private:
        //Inicio sempre essa árvore vazia.
        Node<T,A>* root = nullptr;      

        //Função que me devolve a altura do nó passado como parametro.
        int height(Node<T,A> *node){
            return !node ? 0 : node->height;
        }

        //Função que me devolve o balanço do nó passado como parametro.
        int balance(Node<T,A> *node){
            return height(node->right) - height(node->left);
        }    

        //Função que faz a rotação à direita.
        Node<T,A>* rightRotation(Node<T,A> *p){
            Node<T,A> *u = p->left;
            p->left = u->right;
            u->right = p;

            //recalcular as alturas de P e de U, já que foram mudados de posição.
            p->height = 1 + max(height(p->left),height(p->right));
            u->height = 1 + max(height(u->left), height(u->right));
            return u;
        }

        //Função que faz a rotação à esquerda.
        Node<T,A>* leftRotation(Node<T,A> *p){
            Node<T,A> *u = p->right;
            p->right = u->left;
            u->left = p;

            //recalcular as alturas de P e de U, já que foram mudados de posição.
            p->height = 1 + max(height(p->left),height(p->right));
            u->height = 1 + max(height(u->left), height(u->right));
            return u;
        } 

        //Função que decidirá as rotações.
        Node<T,A>* fixup_node(Node<T,A> *p, T key){
            //O primeiro passo aqui é recalcular a altura desse nó
            //para que seja possível identificar se há necessidade
            //de uma outra rotação no futuro
            p->height = 1 + max(height(p->left),height(p->right));

            //Agora preciso ter noção de como está o balanço
            //deste nó em questão.

            int bal = balance(p); // H(d) - H(e)

            //Aqui começarei a analisar os possíveis casos.

            //Primeiro inicio pensando no caso deste nó não
            //precisar de nenhuma rotação.
            if(bal >= -1 && bal <= 1){
                return p;
            }
            //Caso o balanço do nó seja -2,implica que a subárvore
            //esquerda é maior e, neste caso, o nó que causou o desbalanceamento
            //está a esquerda nesta subárvore. (Caso 1a)
            else if(bal < -1 && key < p->left->key){
                //Solução: rotação simples a direita em p.
                p = rightRotation(p);
            } 
            //Caso o balanço do nó seja -2, implica que a subárvore
            //esquerda é maior e, neste caso, o nó que causou o desbalanceamento
            //está a direita nesta subárvore. (Caso 1b)
            else if(bal < -1 && key > p->left->key){
                //Solução: rotação dupla a direita.
                //Rotação a esquerda no filho esquerdo de p.
                //Rotação a direita em p.
                p->left = leftRotation(p->left);
                p = rightRotation(p);
            }
            //Os próximos casos abordados são simétricos aos casos já vistos.

            //Caso o balanço do nó seja +2, implica que a subárvore
            //direita é maior e, neste caso, o nó que causou o desbalanceamento
            //está a direita nessa subárvore.(Caso 2a)
            else if(bal > 1 && key > p->right->key){
                //Solução: rotação simples a esquerda em p.
                p = leftRotation(p);
            }
            //Caso o balanço do nó seja +2, implica que a subárvore
            //direita é maior e, neste caso, o nó que causou o desbalanceamento
            //está a esquerda nesta subárvore. (Caso 2b)
            else if(bal > 1 && key < p->right->key){
                //Solução: rotação dupla a esquerda.
                //Rotação a direita no filho direito de p.
                //Rotação a esquerda em p.
                p->right = rightRotation(p->right);
                p = leftRotation(p);
            }
            //Por fim, após feito as devidas rotações basta retornar o nó.
            return p;
    }

        //Função privada que organizará a estrutura de A's iguais
        void pushVector(Node<T,A>* node, A person){
            if(node->sameT.size() == 0){
                node->sameT.push_back(node->person);
                node->sameT.push_back(person);
            }else{
                node->sameT.push_back(person);
            }
        }

        //Função privada e recursiva que adiciona nó na árvore.                       
        Node<T,A>* add(Node<T,A> *p, T key, A person){
            if(p == nullptr){
                return new Node<T,A>(key,person);
            }
            if(p->key == key){
                pushVector(p,person);
                return p;
            }else if(p->key < key){
                p->right = add(p->right,key,person);
            }else{
                p->left = add(p->left,key,person);
            }
            //Hora de balancear a arvore.
            p = fixup_node(p,key);
            return p;
        }

        //Função que libera toda a árvore.
        Node<T,A>* clear(Node<T,A> *node){
            if(node != nullptr){
                clear(node->left);
                clear(node->right);
                delete node;
            }
            return nullptr;

        } 

        //Função privada e recursiva que procura um nó na árvore
        Node<T,A>* search(Node<T,A>* node, T key){
            if(node == nullptr){
                return nullptr;
            }
            if(node->key == key){
                return node;
            }else if(node->key < key){
                return search(node->right,key);
            }else{
                return search(node->left,key);
            }
            return nullptr;
        } 

        //Função privada que printa a árvore de uma forma
        //amigável no terminal.
        void bshow(Node<T,A> *node, std::string heranca) const{
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
            std::cout << node->person->name << std::endl;
            if(node != nullptr && (node->left != nullptr || node->right != nullptr))
                bshow(node->left, heranca + "l");
        }
        //Função privada e recursiva que retorna a quantidade 
        //de nós que tem na árvore.
        int qtnodes(Node<T,A> *node){
            if(node == nullptr){
                return 0;
            }
            return 1 + qtnodes(node->left) + qtnodes(node->right);
        }

        //Função privada e recursiva que pesquisa datas de nascimento
        //dentro de um intervalo
        void searchDate(Node<T,A>* node, T min, T max,vector<A> &final){
            if(node == nullptr){
                return;
            }

            if(node->key >= min){
                searchDate(node->left,min,max,final);
            }

            if(node->key >= min && node->key <= max){
                if(node->sameT.size() == 0){
                    final.push_back(node->person);
                }else{
                    for(int i = 0; i < node->sameT.size(); i++){
                        final.push_back(node->sameT[i]);
                    }
                }
            }

            if(node->key <= max){
                searchDate(node->right,min,max,final);
            }
        
        }

        //Função privada e recursiva que pesquisa
        //nomes com as iniciais
        void searchSub(Node<T,A>* node, T sub, vector<A> &final){
            //Busca inoder
            if(node == nullptr){
                return;
            }

            string testValue = node->key.substr(0,sub.size());
            if(testValue == sub){
                if(node->sameT.size() == 0){
                    final.push_back(node->person);
                }else{
                    for(int i = 0; i < node->sameT.size(); i++){
                        final.push_back(node->sameT[i]);
                    }
                }

            }
            if(testValue > sub){
                searchSub(node->left,sub,final);
            }else if(testValue < sub){
                searchSub(node->right,sub,final);
            }else{
                searchSub(node->left,sub,final);
                searchSub(node->right,sub,final);
            }
        }

    public:
        avl() = default; //Construtor padrão.
        avl(const avl& t) = delete; //Deletado construtor de cópias.
        avl& operator=(const avl& t) = delete; //Deletado operador de atribuição.

        //Função pública que retorna a quantidade
        //de nós que tem em uma árvore
        int qtnodes(){
            return qtnodes(root);
        }

        //Função pública que adiciona nós na árvore.
        void add(T k,A person){
            root = add(root,k,person);
        }

        //Função pública que libera toda a árvore.
        void clear(){
            root = clear(root);
        } 

        //Função pública que procura um nó na árvore.
        Node<T,A>* search(T key){
            return search(root,key);
        } 

        //Função pública que printa a árvore
        //de forma amigável no terminal.
        void bshow() const{
            bshow(root, "");
        }

        //Função pública que pesquisa datas de nascimento
        //entre intervalo.
        void searchDate(T min, T max, vector<A> &final){
            searchDate(root,min,max,final);
        }

        //Função publica que pesquisa nomes pelas iniciais.
        void searchSub(T sub, vector<A> &final){
            searchSub(root,sub,final);
        }
};
#endif