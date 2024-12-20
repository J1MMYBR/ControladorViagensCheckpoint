#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include "cidade.h"

using namespace std;

class Passageiro{
    private:
        string nome;
        Cidade* local_atual;

    public:
        Passageiro(string &nome, Cidade* local_atual);

        string getNome();

        Cidade* getLocalAtual();

        void setLocalAtual(Cidade* local);
};

#endif