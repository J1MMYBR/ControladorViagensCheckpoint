#include <iostream>
#include <string>
#include "transporte.h"
#include "cidade.h"

using namespace std;

Transporte::Transporte(const std::string &nome, char tipo_transporte, int capacidade_passageiros, 
                       int velocidade, int distancia_descanso, int tempo_descanso, Cidade* local_atual)
                        : nome(nome), tipo_transporte(tipo_transporte), capacidade_passageiros(capacidade_passageiros), 
                        velocidade(velocidade), distancia_descanso(distancia_descanso), tempo_descanso(tempo_descanso), 
                        local_atual(local_atual) {}



char Transporte::getTipoTransporte() {
    return tipo_transporte;
}

int Transporte::getCapacidadePassageiros() {
    return capacidade_passageiros;
}

int Transporte::getVelocidade() {
    return velocidade;
}

int Transporte::getDistanciaDescanso() {
    return distancia_descanso;
}

int Transporte::getTempoDescanso() {
    return tempo_descanso;
}

Cidade* Transporte::getLocalAtual() {
    return local_atual;
}

void Transporte::setLocalAtual(Cidade* local) {
    this->local_atual = local;
}

string Transporte::getNome() const{
    return nome;
}
