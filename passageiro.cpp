#include <string>
#include "passageiro.h"
#include "cidade.h"

using namespace std;

Passageiro::Passageiro(string &nome, Cidade *local_atual)
    : nome(nome), local_atual(local_atual) {}

string Passageiro::getNome(){
    return nome;
}

Cidade *Passageiro::getLocalAtual(){
    return local_atual;
}

void Passageiro::setLocalAtual(Cidade *local){
    this->local_atual = local;
}