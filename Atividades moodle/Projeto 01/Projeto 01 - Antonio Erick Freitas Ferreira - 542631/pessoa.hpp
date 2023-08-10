#ifndef PESSOA_HPP
#define PESSOA_HPP
#include <iostream>
#include <string>
#include "date.hpp"
#include "cpf.hpp"

class Pessoa{
    public:

    Cpf myCpf;
    std::string name;
    std::string lastName;
    Date dataNascimento;
    std::string cidadeNatal;

    //Construtor sem parametros deletado.
    Pessoa() = delete;

    Pessoa(Cpf cpfOutside, std::string name, std::string lastName, Date dataNascimento, std::string cidadeNatal){
        this->myCpf = cpfOutside;
        this->name = name;
        this->lastName = lastName;
        this->dataNascimento = dataNascimento;
        this->cidadeNatal = cidadeNatal;
    }
};
#endif