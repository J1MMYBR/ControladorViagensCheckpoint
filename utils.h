#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "cidade.h"
#include "passageiro.h"
#include "trajeto.h"
#include "transporte.h"
#include "viagem.h"

void menu();
int interacao();
void criarArquivos();

void cadastroCidade();
void cadastroPassageiro();
void cadastroTrajeto();
void cadastroTransporte();
void cadastroViagem();

#endif