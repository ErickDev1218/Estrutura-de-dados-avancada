#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

//Busca em largura
void BFS(const vector<list<int>>& grafo,int vertices){
    //Criação e primeira coloração de cada vertice.
    vector<string> color;
    color.resize(grafo.size());
    for(int i = 0; i < grafo.size(); i++){
        color[i] = "undefined";
    }
    queue<int> fila; //Fila vazia.
    //Faço o loop pois quando coloquei a dedo, estava testando apenas
    //para a vizinhança do vertice colocado a dedo e onde seus vizinhos 
    //alcançavam. Para testar o grafo todo, se fez necessário o uso
    //do loop e o if. O if é justamente para saber se por exemplo:
    //a partir do 0 o algoritmo não encontrou o vertice 5, então 5 será undefined.
    //Por sua vez, como o index está em loop, o vertice 5 será alcançado (será undefined) 
    //pelo algoritmo e será pintado como diz o problema.
    for(int index = 0; index < grafo.size(); index++){ 
        if(color[index] == "undefined"){ 
            fila.push(index); //Coloco na fila o primeiro vertice.
            color[index] = "Red";//Pinto de vermelho o primeiro vertice.
            while(!fila.empty()){
                int u = fila.front(); //Pego o primeiro da fila.
                fila.pop();//Retiro o primeiro da fila.
                for(int v : grafo[u]){
                    //Tomada de decisão para pintura de um vertice ainda não visitado.
                    if(color[v] == "undefined"){
                        if(color[u] == "Red"){
                            color[v] = "Blue";
                        }else if(color[u] == "Blue"){
                            color[v] = "Red";
                        }
                        fila.push(v);
                    }else if(color[v] == color[u]){
                        cout << "Não!" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "Sim!" << endl;
}

int main(){
    fstream arq;
    arq.open("grafos.txt");
    int n,m,u,v;
    //n = número de vertices.
    //m = número de arestas.
    //(u,v) = vizinhança.
    while(!arq.eof()){//Enquanto não chegar no fim do arquivo.
        arq >> n >> m;
        //cout << "Numero de vertices = " << n << endl << "Numero de arestas = " << m << endl;
        vector<list<int>> grafo;
        grafo.resize(n);//Faço o vector ter tamanho n.
        for(int i = 0; i < m; i++){
            arq >> u >> v; //Leio u e v
            grafo[u].push_back(v); //Crio o par (u,v).
            //cout << "(" << u << "," << v << ") - ";
        }
        //Função que diz se posso pintar um grafo com apenas 2 cores ('Red' ou 'Blue')
        //de modo que nenhum grafo vizinho tenha a mesma cor ou seja, o grafo pode ser bipartido
        //ou visto como 2 conjuntos onde elementos do mesmo conjunto não façam vizinhança entre si.
        BFS(grafo,n); 
    }
}