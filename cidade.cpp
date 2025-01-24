#include "cidade.h"

using namespace std;

Cidade::Cidade(const string &nome, int indice) 
    : nome(nome), indice(indice) {}

string Cidade::getNome() const {
    return this->nome;
}

void Cidade::setNome(const string &novoNome) {
    this->nome = novoNome;
}

int Cidade::getIndice() const {
    return this->indice;
}

void Cidade::setIndice(int novoIndice) {
    this->indice = novoIndice;
}
