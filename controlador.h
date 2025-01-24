#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <vector>
#include <list>
#include <string>
#include <utility>
#include "cidade.h"
#include "trajeto.h"
#include "transporte.h"
#include "viagem.h"
#include "passageiro.h"

using namespace std;

class ControladorDeTransito {
private:
    int tempoCorrido;
    vector<Cidade*> cidades;
    vector<Trajeto*> trajetos;
    vector<Transporte*> transportes;
    vector<Viagem*> viagens;
    vector<Passageiro*> passageiros;

    struct Edge {
        int destino;
        int distancia;
    };

    pair<vector<int>, vector<int>> dijkstra(int origem, const vector<vector<Edge>>& grafo);
    vector<int> reconstruirCaminho(int origem, int destino, const vector<int>& antecessor);
    list<Cidade*> gerarCidadesViagem(vector<int> caminho);

public:
    ControladorDeTransito();
    
    Cidade* buscarCidade(const string& nome);
    Transporte* buscarTransporte(const string& nome);
    Passageiro* buscarPassageiro(const string& nome);
    Trajeto* buscarTrajeto(Cidade* origem, Cidade* destino);

    void avancarTempo(int horas);
    void finalizarViagem(Viagem* viagem);
    pair<list<Cidade*>, int> calcularMelhorRota(Cidade& origem, Cidade& destino, char tipo);

    void cadastrarCidade(const string& nome, const int indice);
    void cadastrarTrajeto(const string& nomeOrigem, const string& nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(const string& nome, char tipo, int capacidade, int velocidade, int distanciaDescanso, int tempoDescanso, const string& localAtual);
    void cadastrarPassageiro(const string &nome, const string &localAtual);
    void iniciarViagem(const string& nomeTransporte, const vector<string>& nomesPassageiros, const string& nomeOrigem, const string& nomeDestino);
    void relatarEstado();
};

#endif
