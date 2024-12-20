#ifndef VIAGEM_CPP
#define VIAGEM_CPP

#include <iostream>
#include <string>
#include <vector>
#include "cidade.h"
#include "transporte.h"
#include "passageiro.h"

using namespace std;

class Viagem {
    private: 
        Transporte* transporte; // Ponteiro para o transporte utilizado na viagem
        vector<Passageiro*> passageiros; // Vetor de ponteiros para os passageiros da viagem
        Cidade* origem; // Ponteiro para a cidade de origem da viagem
        Cidade* destino; // Ponteiro para a cidade de destino da viagem
        Viagem* proxima; // Ponteiro para a próxima viagem 
        int horasEmTransito; // Quantidade de horas que a viagem está em andamento
        bool emAndamento; // Indica se a viagem está em progresso ou foi concluída

    public:
        // Construtor da classe, inicializa os atributos principais da viagem
        Viagem(Transporte* transporte, vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);

        // Método para iniciar a viagem, verifica condições iniciais e ajusta o estado
        void iniciarViagem();

        // Método para avançar o tempo em horas e calcular o progresso da viagem
        void avancarHoras(int horas);
        
        // Método para relatar o estado atual da viagem
        void relatarEstado() ;
        
        // Método para verificar se a viagem está em andamento
        bool isEmAndamento();
};


#endif