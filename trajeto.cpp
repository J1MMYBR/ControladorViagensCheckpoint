#include <iostream>
#include <string>
#include "trajeto.h"
#include "cidade.h"

using namespace std;

Trajeto::Trajeto(Cidade *origem, Cidade *destino, char tipo_trajeto, int distancia_trajeto)
    : origem(origem), destino(destino), tipo_trajeto(tipo_trajeto), distancia_trajeto(distancia_trajeto) {} 

Cidade *Trajeto::getOrigem(){
    return this->origem;
}

Cidade *Trajeto::getDestino(){
    return this->destino;
}

char Trajeto::getTipoTrajeto(){
    return this->tipo_trajeto;
}

int Trajeto::getDistancia(){
    return this->distancia_trajeto;
}
