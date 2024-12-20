#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <iostream>
#include <string>
#include "cidade.h"

using namespace std;

class Transporte{
private: 
    string nome;
    char tipo_transporte; // A (aquático) ou T (terrestre)
    int capacidade_passageiros;
    int velocidade; // km/h
    int distancia_descanso; // km
    int tempo_descanso; // h
    Cidade* local_atual;

public: 
    Transporte(string &nome, char tipo_transporte, int capacidade_passageiros, int velocidade, int distancia_descanso, int tempo_descanso, Cidade* local_atual);

    char getTipoTransporte();

    int getCapacidadePassageiros();
        
    int getVelocidade();

    int getDistanciaDescanso();

    int getTempoDescanso();

    /*int getTempoDescansoAtual(){

    } */

    Cidade* getLocalAtual();

    void setLocalAtual(Cidade* local);

};

#endif