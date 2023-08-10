#include <iostream>
#include "avl.hpp"
#include "cpf.hpp"
#include "date.hpp"
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


vector <Pessoa*> arquivo(string file){
    ifstream csv;
    csv.open(file); //Abro o arquivo.
    vector<Pessoa*> final;

    if(csv.is_open()){ //Se o arquivo estiver sido aberto com sucesso
        string ignora;
        getline(csv,ignora); //Ignorando a primeira linha.

        string line;
        while(getline(csv,line)){
            string cpfOutside,nome,sobrenome,dataNascimento,cidadeNatal;
            int posicao;
            

            posicao = line.find(","); //Achando a posição da primeira virgula no arquivo.
            cpfOutside = line.substr(0,posicao); //Função que isola o cpf do resto da frase.

            line.erase(0,posicao+1); //Apagando o cpf da linha.
            posicao = line.find(",");//Achando a posição da primeira virgula no arquivo.
            nome = line.substr(0,posicao);//Função que isola o nome do resto da frase.

            line.erase(0,posicao+1); //Apagando o nome da linha.
            posicao = line.find(",");//Achando a posição da primeira virgula no arquivo.
            sobrenome = line.substr(0,posicao);//Função que isola o sobrenome do resto da frase.
            
            line.erase(0,posicao+1); //Apagando o sobrenome da linha.
            posicao = line.find(","); //Achando a posição da primeira virgula no arquivo.
            dataNascimento = line.substr(0,posicao);//Função que isola a data de nascimento do resto da frase.

            line.erase(0,posicao+1);//Apagando a data de nascimento da linha.
            posicao = line.find(",");//Achando a posição da primeira virgula no arquivo.
            cidadeNatal = line.substr(0,posicao);//Função que isola a cidade natal do resto da frase

            
            Date myDate(dataNascimento);
            Cpf myCpf(cpfOutside);
            Pessoa *n = new Pessoa(myCpf,nome,sobrenome,myDate,cidadeNatal);
            final.push_back(n);
        }
        csv.close(); //fecho o arquivo.
    }else{
        cout << "ERROR: Nao foi possivel abrir o arquivo." << endl;
    }
    return final;
}

//Função que recebe um objeto do tipo Pessoa* e
//printa seus atributos.
void print(Pessoa* person){
    cout << person->myCpf.cpfAlf << " " << person->name << " " << person->lastName << " " << person->dataNascimento.dataAlf << " "
    << person ->cidadeNatal << endl;
}

int main(){

    vector <Pessoa*> pop = arquivo("data.csv"); //Vector que tem todas a pessoas do arquivo.

    //Criação das 3 árvores.
    avl<Cpf,Pessoa*> *cpfTree = new avl<Cpf,Pessoa*>();
    avl<Date,Pessoa*> *dnTree = new avl<Date,Pessoa*>();
    avl<string,Pessoa*> *nameTree = new avl<string,Pessoa*>();

    //Adicionando cada pessoa na sua árvore correspondente.
    for(int i = 0; i < pop.size(); i++){
        cpfTree->add(pop[i]->myCpf,pop[i]);
        dnTree->add(pop[i]->dataNascimento,pop[i]);
        nameTree->add(pop[i]->name,pop[i]);
    }

    cout << "----------------------------------------" << endl;
    cout << "|             BEM-VINDO                |" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl << "O que você gostaria de fazer no sistema ?" << endl;
    cout << "1 -> Pesquisar por CPF." << endl << "2 -> Pesquisar por nome." << endl
    << "3 -> Pesquisar por data de nascimento." << endl << "4 -> Para ver uma árvore." <<
    endl <<  "5 -> Para ver o menu novamente." << endl << "999 -> Para encerrar o programa." << endl;

    int menu; //Inteiro que fará o menu.
    do{
        cin >> menu;
        if(menu == 999){
            //Deleto tudo que criei com new.
            cpfTree->clear();
            dnTree->clear();
            nameTree->clear();
            for(int i = 0; i < pop.size();i++){
                delete pop[i];
            }
            cout << "Até mais! =)" << endl;
            break;
        }else if(menu == 1){ //Pesquisa por CPF
            cin.ignore(); //limpo o buffer

            string received;
            cout << "Digite o CPF: ";
            cin >> received;

            Cpf myCpf(received);
            Node<Cpf,Pessoa*> *p = cpfTree->search(myCpf);

            //Testo se o CPF inserido está na árvore
            if(p != nullptr){
                print(p->person);
            }else{
                cout << "Este CPF não está cadastrado!" << endl;
            }

        }
        else if(menu == 2){//Pesquisa por nome
            int n;
            cout << "1 -> Pesquisar todas as pessoas que tenha um determinado nome." << endl
            << "2 -> Pesquisar todas as pessoas que comecem com uma string." << endl;
            cin >> n;
            if(n == 1){ 
                cin.ignore(); //limpo o buffer
                string nome;
                cout << "Digite o nome que você procura: ";
                cin >> nome;

                Node<string,Pessoa*> *p = nameTree->search(nome);
                if(p != nullptr){
                    if(p->sameT.size() != 0){//Significa que tenho mais de uma pessoa com este nome
                        cout << "Há mais de uma pessoa com este nome, segue os mesmos abaixo: " << endl;
                        for(int i = 0; i < p->sameT.size(); i++){
                            print(p->sameT[i]);
                        }
                    }else{
                        print(p->person);
                    }
                }else{
                    cout << "Não há ninguém com este nome!" << endl;
                }
            }else if(n == 2){
                cin.ignore(); //limpo o buffer
                string sub;
                cout << "Digite a substring: ";
                cin >> sub;

                vector <Pessoa*> containsSub;
                nameTree->searchSub(sub,containsSub);

                if(containsSub.size() > 0){
                    for(int i = 0; i < containsSub.size(); i++){
                        print(containsSub[i]);
                    }
                }else if(containsSub.size() == 0){
                    cout << "Não há ninguém que tenha essa substring." << endl;
                }
            }
            
        }
        else if(menu == 3){//Pesquisa por data de nascimento

            cout << "1 -> Data especifica." << endl << "2 -> Intervalo de datas." << endl;
            int d;
            cin >> d;
            
            if(d == 1){
                cin.ignore(); //limpo o buffer
                string dataNascimento;
                cout << "Digite a data de nascimento: ";
                cin >> dataNascimento;

                Date myDate(dataNascimento);
                Node<Date,Pessoa*> *p = dnTree->search(myDate);    

                if(p != nullptr){
                    if(p->sameT.size() != 0){//Significa que tenho mais de uma pessoa com este nome
                        cout << "Há mais de uma pessoa com esta data de nascimento, segue os mesmos abaixo: " << endl;
                        for(int i = 0; i < p->sameT.size(); i++){
                            print(p->sameT[i]);
                        }
                    }else{
                        print(p->person);
                    }
                }else{
                    cout << "Não há ninguém com esta data de nascimento!" << endl;
                }
            }else if(d == 2){
                cin.ignore(); // limpo o buffer
                cout << "Digite qual o intervalo das datas (menor data - maior data): " << endl;
                string d1;
                string d2;
                cin >> d1;
                cin >> d2;

                Date infLim(d1);
                Date supLim(d2);

                vector<Pessoa*> intervalDate;
                dnTree->searchDate(infLim,supLim,intervalDate);
                if(intervalDate.size() > 0) {
                    for(int i = 0; i < intervalDate.size(); i++){
                        print(intervalDate[i]);
                    }
                }else if(intervalDate.size() == 0){
                    cout << "Não há ninguém neste intervalo de datas." << endl;
                }
            }
        }    
        else if(menu == 4){ //Ver uma árvore
            cin.ignore(); //limpo o buffer
            string tipo;
            cout << "(Nome - Cpf - DataDeNascimento)" << endl;
            cout << "Digite o tipo de árvore a ser vista: ";
            cin >> tipo;

            if(tipo == "Nome"){
                nameTree->bshow();
                cout << "Nesta árvore temos " << nameTree->qtnodes() << " nós!" << endl;
            }else if(tipo == "Cpf"){
                cpfTree->bshow();
                cout << "Nesta árvore temos " << cpfTree->qtnodes() << " nós!" << endl;
            }else if(tipo == "DataDeNascimento"){
                dnTree->bshow();
                cout << "Nesta árvore temos " << dnTree->qtnodes() << " nós!" << endl;
            }

        }
        else if(menu == 5){
            cout << "1 -> Pesquisar por CPF." << endl << "2 -> Pesquisar por nome." << endl
            << "3 -> Pesquisar por data de nascimento." << endl << "4 -> Para ver uma árvore." <<
            endl <<  "5 -> Para ver o menu novamente." << endl << "999 -> Para encerrar o programa."
            << endl;
        }
    }while(true);
    
    
}