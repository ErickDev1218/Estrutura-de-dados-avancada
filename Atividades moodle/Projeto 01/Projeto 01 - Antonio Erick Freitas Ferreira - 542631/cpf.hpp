#ifndef CPF_HPP
#define CPF_HPP
#include <iostream>
#include <string>

class Cpf{
    public:
        std::string cpfAlf;
        int first;
        int second;
        int third;
        int last;

        Cpf() = default;
        //Formato recebido 000.000.000-00
        Cpf(std::string received){
            cpfAlf = received;       

            int aux = received.find(".");
            first = stoi(received.substr(0,aux));
            received.erase(0,aux+1);

            aux = received.find(".");
            second = stoi(received.substr(0,aux));
            received.erase(0,aux+1);

            aux = received.find("-");
            third = stoi(received.substr(0,aux));
            received.erase(0,aux+1);

            last = stoi(received);
        }

        void print(){
            std::cout << cpfAlf << " ";
        }

        bool operator>(const Cpf& n) const{
            if(first > n.first){
                return true;
            }else if(first == n.first && second > n.second){
                return true;
            }else if(first == n.first && second == n.second && third > n.third){
                return true;
            }else if(first == n.first && second == n.second && third == n.third && last > n.last){
                return true;
            }
            return false;
        }

        bool operator<(const Cpf& n) const{
            if(first < n.first){
                return true;
            }else if(first == n.first && second < n.second){
                return true;
            }else if(first == n.first && second == n.second && third < n.third){
                return true;
            }else if(first == n.first && second == n.second && third == n.third && last < n.last){
                return true;
            }
            return false;
        }

        bool operator==(const Cpf& n) const{
            if(first == n.first && second == n.second && third == n.third && last == n.last){
                return true;
            }
            return false;
        }
};


#endif