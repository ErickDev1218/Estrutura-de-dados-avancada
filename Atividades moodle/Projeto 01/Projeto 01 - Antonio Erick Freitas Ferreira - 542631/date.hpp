#ifndef DATE_HPP
#define DATE_HPP
#include <iostream>
#include <string>

class Date{
    public:
        std::string dataAlf;
        int day;
        int month;
        int year;

        Date() = default;

        //Formato recebido 00/00/0000
        Date(std::string dataNascimento){
            dataAlf = dataNascimento;
            std::string aux;

            //Tratando a string recebida para
            //conversão em int
            int x = dataNascimento.find("/");
            aux = dataNascimento.substr(0,x);
            month = stoi(aux);
            dataNascimento.erase(0,x+1);

            x = dataNascimento.find("/");
            aux = dataNascimento.substr(0,x);
            day = stoi(aux);
            dataNascimento.erase(0,x+1);

            year = stoi(dataNascimento);
        }

        bool operator>(const Date& n) const{
            if(year > n.year){
                return true;
            }else if(year == n.year && month > n.month){
                return true;
            }else if(year == n.year && month == n.month && day > n.day){
                return true;
            }
            return false;
        }

        bool operator<(const Date& n) const{
            if(year < n.year){
                return true;
            }else if(year == n.year && month < n.month){
                return true;
            }else if(year == n.year && month == n.month && day < n.day){
                return true;
            }
            return false;
        }

        bool operator==(const Date& n) const{
            if(year == n.year && month == n.month && day == n.day){
                return true;
            }
            return false;
        }

        bool operator>=(const Date& n) const{
            if(year > n.year){
                return true;
            }else if(year == n.year && month > n.month){
                return true;
            }else if(year == n.year && month == n.month && day > n.day || day == n.day){
                return true;
            }
            return false;
        }
        bool operator<=(const Date& n) const{
            if(year < n.year){
                return true;
            }else if(year == n.year && month < n.month){
                return true;
            }else if(year == n.year && month == n.month && day < n.day || day == n.day){
                return true;
            }
            return false;
        }
};


#endif