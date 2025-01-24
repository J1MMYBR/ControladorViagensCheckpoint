#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include "cidade.h"

using namespace std;

class Passageiro {
private:
    std::string nome;
    Cidade* local_atual; 

public:
    Passageiro(const std::string& nome, Cidade* localAtual);
    std::string getNome();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};

#endif