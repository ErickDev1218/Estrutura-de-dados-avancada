#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <utility>
#include <algorithm>
using namespace std;

int global = 0;
vector <pair<int,int>> pontes;

void DFSVisit(vector<list<int>> grafo, int i,vector<string>& color, vector<int>& upper, vector<int>& lower, vector<int>& pi,vector<int>& minTime){
    global++;
    lower[i] = global; // Tempo de descoberta
    color[i] = "Cinza"; //Vertice já descoberto
    int filhos = 0; //Conta quantos filhos o vertice tem
    minTime[i] = global; //Menor tempo de descoberta

    //Para cada elemento na adj. pesquise.
    for(auto& k : grafo[i]){
        if(color[k] == "Branco"){
            pi[k] = i;
            filhos++;
            DFSVisit(grafo,k,color,upper,lower,pi,minTime); 
            minTime[i] = min(minTime[i],minTime[k]);
            if(minTime[k] > minTime[i]){
                pontes.push_back(make_pair(i,k));
            }
        }else if(k != pi[i]){
            minTime[i] = min(minTime[i],minTime[k]);
        }

    } 
    color[i] = "Preto";
    global++;
    upper[i] = global;

}

void DFS(vector <list<int>> grafo){
    pontes.clear();
    vector<string> color(grafo.size(),"Branco"); //Inicio o vetor de cores todos brancos
    vector<int> pi(grafo.size(),-1); //-1 representa que não há pai para o vertice
    vector<int> upperTime(grafo.size(),0); //Tempo de encerramento
    vector<int> lowerTime(grafo.size(),0);//Tempo de descoberta
    vector<int> minTime(grafo.size(),0);//Menor tempo entre o vertice e seus vizinhos

    global = 0;

    for(int i = 0; i < grafo.size();i++){
        if(color[i] == "Branco"){
            DFSVisit(grafo,i,color,upperTime,lowerTime,pi,minTime);
        }
    }
}

int main(){
    fstream arq;
    arq.open("grafo2.txt");
    int n, m;
    arq >> n >> m;
    vector <list<int>> grafo; //Grafo nao direcionado
    vector <list<int>> grafoDirec; //Grafo direcionado
    grafo.resize(n);
    grafoDirec.resize(n);

    if(arq.is_open()){
        for(int i = 0; i < m; i++){
            int u, v;
            arq >> u >> v;
            grafo[u].push_back(v); // Criando (u,v)
            grafo[v].push_back(u); //Criando (v,u) por ser não direcionado

            grafoDirec[u].push_back(v);// Criando (u,v) no grafo direcionado
        }
        
    }

    DFS(grafo);// Essa função irá descobrir as pontes.

    //Adicionando a aresta ponte de volta.
    for(int i = 0; i < pontes.size();i++){
        int u = pontes[i].first;
        int v = pontes[i].second;

        grafoDirec[v].push_back(u);
    }

    //Corrigindo vertices que deveriam ter saída mas não tem.
    for(int i = 0; i < grafoDirec.size(); i ++){
        if(grafoDirec[i].size() == 0){ // Lista vazia
            int min = grafo[i].front();
            for(int& k : grafo[i]){
                if(k < min){
                    min = k; //achando o menor;
                }
            }
            grafoDirec[i].push_back(min); //Adicionando a aresta
            grafoDirec[min].remove(i); //Removendo a aresta que não é ponte
        }
    }

    //Deixando o grafo em ordem para a impressão
    for(int i = 0; i < grafoDirec.size(); i++){
        grafoDirec[i].sort();
    }

    //Imprimindo o grafo
    for(int i = 0; i < grafoDirec.size(); i++){
        for(int& k : grafoDirec[i]){
            cout << "(" << i << "," << k << ")" << endl;
        }
    }
    cout << "#" << endl;
}