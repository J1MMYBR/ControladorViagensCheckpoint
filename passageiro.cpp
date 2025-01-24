#include <string>
#include "passageiro.h"
#include "cidade.h"

Passageiro::Passageiro(const std::string& nome, Cidade* localAtual)
    : nome(nome), local_atual(localAtual) {}

std::string Passageiro::getNome() {
    return nome;
}

Cidade* Passageiro::getLocalAtual() {
    return local_atual;
}

void Passageiro::setLocalAtual(Cidade* local) {
    this->local_atual = local;
}