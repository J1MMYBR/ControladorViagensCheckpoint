#ifndef VIAGEM_CPP
#define VIAGEM_CPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "cidade.h"
#include "transporte.h"
#include "passageiro.h"

using namespace std;

class Viagem {
    private: 
        Transporte* transporte;     
        vector<Passageiro*> passageiros; 
        Cidade* origem; 
        Cidade* destino; 
        Viagem* proxima;  
        int horasEmTransito;
        bool emAndamento; 

    public:
        Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Cidade* origem, Cidade* destino, int horasEmTransito, bool emAndamento);

        Cidade* getOrigem();

        Cidade* getDestino();

        void iniciarViagem();

        void avancarHoras(int horas);
        
        void relatarEstado() ;
        
        bool isEmAndamento();

        std::string conversorCSV() const;

        static void salvarViagens(const std::vector<Viagem>& viagens);
        
        static void carregarViagens(std::vector<Viagem>& viagens, const std::vector<Cidade>& cidades, const std::vector<Transporte>& transportes);

        bool getStatus() const;

        void setTempoRestante(int horas);
        
        int getTempoRestante() const;
        
        Transporte* getTransporte();
        
        void setStatus(bool status);
        
        std::vector<Passageiro*> getPassageiros() const;

};


#endif