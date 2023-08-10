#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

int BFS(const unordered_map <string,vector<pair<string,string>>> hash,string n){
    string kb = "Kevin Bacon";
    
    if(n == kb){ //É o KB
        return -2;
    }
    queue<pair<string,int>> fil;
    fil.push({n,0});

    unordered_set<string> cinzas;
    cinzas.insert(n);

    while(!fil.empty()){
        string nome = fil.front().first;
        int bn = fil.front().second;
        fil.pop();

        if(nome == kb){
            return bn;
        }
        for(auto& i : hash.at(nome)){
            string vizinho = i.second;
            if(cinzas.find(vizinho) == cinzas.end()){
                
                fil.push({vizinho,bn+1});
                cinzas.insert(vizinho);
            }
        }
    }    
    return -1; //sinaliza que nao chegou ao KB
    
}

void baconNum(const unordered_map <string,vector<pair<string,string>>> hash,vector<string> nomes){
    sort(nomes.begin(),nomes.end());

    for(string& i : nomes){
        int bacon = BFS(hash,i);
        if(bacon == -1){
            //Não chegou ao Kevin Bacon
        }else if(bacon == -2){
            cout  << "O número de Bacon de " << i << " é " << 0 << " pelo fime " << endl;
        }else{
            cout << "O número de Bacon de " << i << " é " << bacon << " pelo fime " << hash.at(i)[0].first << endl;
        }
    }
}

int main(){
    fstream input;

    input.open("input.txt");

    if(!input.is_open()){
        cout << "Error ao abrir o arquivo!" << endl;
    }
    vector<string> nomes;
    vector<string> filmes;
    vector<string> vizinhos;
    vector<string> geral;
    string line;
    while(getline(input,line)){
        stringstream ss {line};

        string token;

        while(getline(ss,token,';')){
            geral.push_back(token);
        }
    }

    for(int i = 0; i < geral.size();i++){
        if(i%3 == 0){
            nomes.push_back(geral[i]);
        }else if(i%3 == 1){
            filmes.push_back(geral[i]);
        }else if(i%3 == 2){
            vizinhos.push_back(geral[i]);
        }
    }
    /*
    int contador = 0;
    for(auto& i : nomes){
        cout << i << " ";
        for(auto& k : vizinhos){
            cout << k << " ";
            if(i == k){
                contador++;
            }
        }
        cout << endl;
    }
    cout << contador << endl;
    */

    unordered_map <string,vector<pair<string,string>>> hash;

    for(int i = 0; i < nomes.size();i++){
        string u = nomes[i];
        string edge = filmes[i];
        string v = vizinhos[i];

        hash[u].emplace_back(edge,v);
    }
    for(int i = 0; i < nomes.size(); i++){
        string u = nomes[i];
        string edge = filmes[i];
        string v = vizinhos[i];

        hash[v].emplace_back(edge,u);
    }
    /*
    for(auto& i : hash){
        cout << "(" << i.first << ")" << endl;
        if(i.first == "Kevin Bacon"){
            cout << "Kevin" << endl;
            break;
        }
        
        for(auto& k : i.second){
            cout << "{ " << k.first << " , " << k.second << "} ";
        }
        cout << endl;
        
    }
    */
    nomes.clear();
   for(auto&i : hash){
        nomes.push_back(i.first);
    }
   baconNum(hash,nomes);
    
}