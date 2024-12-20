#ifndef CIDADE_H
#define CIDADE_H

#include <string> // Inclua apenas o necessário

using namespace std;

class Cidade {
private:
    string nome;

public:
    // Construtor
    Cidade(string &nome);

    // Getters e Setters
    string getNome() const;
    void setNome(const string &novoNome);
};

#endif
