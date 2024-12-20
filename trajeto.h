#ifndef TRAJETO_H
#define TRAJETO_H

#include <iostream>
#include <string>
#include "cidade.h"

using namespace std;

class Trajeto{
private: 
    Cidade* origem;
    Cidade* destino;
    char tipo_trajeto; // A (aquático) ou T (terrestre)
    int distancia_trajeto; // em km

public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo_trajeto, int distancia_trajeto);

    Cidade* getOrigem();

    Cidade* getDestino();

    char getTipoTrajeto();

    int getDistancia();
};

#endif