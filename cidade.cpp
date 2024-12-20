#include <string>
#include "cidade.h"

using namespace std;

// Implementação do construtor
Cidade::Cidade(string &nome) : nome(move(nome)) {}

// Implementação do getter
string Cidade::getNome() const {
    return this->nome;
}

// Implementação do setter
void Cidade::setNome(const string &novoNome) {
    nome = novoNome;
}
