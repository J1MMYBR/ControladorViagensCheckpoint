#ifndef CIDADE_H
#define CIDADE_H

#include <iostream>
#include <string>

using namespace std;

class Cidade {
private:
    string nome;
    int indice;

public:
    Cidade(const string &nome, int indice);

    string getNome() const;
    void setNome(const string &novoNome);

    int getIndice() const; 
    void setIndice(int novoIndice); 
};

#endif
