#include <iostream>
#include <string>
#include <vector>
#include "viagem.h"
#include "cidade.h"
#include "transporte.h"
#include "passageiro.h"

using namespace std;

Viagem::Viagem(Transporte *transporte, vector<Passageiro*> passageiros, Cidade *origem, Cidade *destino) 
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino) {}

void Viagem::iniciarViagem() {
    if (transporte == nullptr || origem == nullptr || destino == nullptr) { // Verifica se as informações essenciais estão presentes
        cout << "Erro: Informações insuficientes para iniciar a viagem." << endl;
        return;
    }
            
    this->emAndamento = true; // Define que a viagem está em andamento
    this->horasEmTransito = 0; // Reseta as horas em trânsito
    this->transporte->setLocalAtual(this->origem); // Define o transporte na origem

    for (Passageiro* passageiro : this->passageiros) { // Atualiza a localização inicial de todos os passageiros para a origem
        passageiro->setLocalAtual(this->origem);
    }

            // Exibe mensagem indicando o início da viagem
    cout << "Viagem iniciada de " << this->origem->getNome() << " para " << this->destino->getNome() << endl;
}

void Viagem::avancarHoras(int horas) {
    if (!this->emAndamento) {// Impede avanço de horas se a viagem não estiver em andamento
        cout << "Erro: A viagem não está em andamento." << endl;
        return;
    }

            // Calcula a distância restante para o destino
    int distanciaRestante = this->destino->getNome() != this->transporte->getLocalAtual()->getNome() ? (this->transporte->getDistanciaDescanso() - this->horasEmTransito) : 0;
            
    int distanciaPercorrida = this->transporte->getVelocidade() * horas; // Calcula a distância percorrida no tempo informado
    this->horasEmTransito += horas; // Incrementa as horas em trânsito

    if (distanciaPercorrida >= distanciaRestante) { // Caso a viagem alcance ou exceda o destino               
        this->transporte->setLocalAtual(this->destino); // Atualiza a posição do transporte para o destino               
                
        for (Passageiro* passageiro : this->passageiros) { // Atualiza a localização de todos os passageiros para o destino
            passageiro->setLocalAtual(this->destino);
        }

        this->emAndamento = false; // Marca a viagem como concluída
        cout << "Viagem concluída! Chegamos ao destino: " << this->destino->getNome() << endl;

    } else {
                // Caso ainda reste distância para o destino
        cout << "Viagem em progresso. " << distanciaRestante - distanciaPercorrida << " km restantes." << endl;
    }
}
        
        
void Viagem::relatarEstado() { // Método para relatar o estado atual da viagem
    cout << "Status da Viagem:" << endl;
    cout << "Origem: " << this->origem->getNome() << endl; // Exibe a origem da viagem
    cout << "Destino: " << this->destino->getNome() << endl; // Exibe o destino da viagem
    cout << "Local Atual do Transporte: " << this->transporte->getLocalAtual()->getNome() << endl; // Local atual do transporte
    cout << "Horas em trânsito: " << this->horasEmTransito << endl; // Horas de viagem já realizadas
    cout << "Status: " << (this->emAndamento ? "Em andamento" : "Concluída") << endl; // Status da viagem
}
        
        
bool Viagem::isEmAndamento() { // Método para verificar se a viagem está em andamento
    return this->emAndamento; // Retorna o status da viagem
}
