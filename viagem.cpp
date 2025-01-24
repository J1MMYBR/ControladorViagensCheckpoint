#include <iostream>
#include <string>
#include <vector>
#include "viagem.h"
#include "cidade.h"
#include "transporte.h"
#include "passageiro.h"

using namespace std;

Viagem::Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Cidade* origem, Cidade* destino, int horasEmTransito, bool emAndamento)
    : transporte(transporte),
      passageiros(passageiros),
      origem(origem),
      destino(destino),
      proxima(nullptr), // Inicializa com nullptr por padrão
      horasEmTransito(horasEmTransito),
      emAndamento(emAndamento) {}

    
Cidade* Viagem::getOrigem() {
    return origem;
}

Cidade* Viagem::getDestino() {
    return destino;
}

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

std::string Viagem::conversorCSV() const {
    std::ostringstream oss;

    oss << transporte->getNome() << ","  // Transporte
        << origem->getNome() << ","      // Origem
        << destino->getNome() << ","     // Destino
        << (proxima ? proxima->origem->getNome() : "NULL") << "," // Próxima viagem
        << horasEmTransito << ","        // Horas em trânsito
        << (emAndamento ? "true" : "false") << ","; // Status da viagem

    // Adiciona os passageiros ao CSV
    if (!passageiros.empty()) {
        for (size_t i = 0; i < passageiros.size(); ++i) {
            oss << passageiros[i]->getNome();
            if (i != passageiros.size() - 1) {
                oss << "|"; // Delimitador entre os passageiros
            }
        }
    } else {
        oss << "NULL"; // Sem passageiros
    }

    return oss.str();
}

void Viagem::salvarViagens(const std::vector<Viagem>& viagens) {
    std::ofstream arquivo("viagens.csv");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo viagens.csv!" << std::endl;
        return;
    }

    // Escreve o cabeçalho no CSV
    arquivo << "Transporte,Origem,Destino,Proxima,Horas_Em_Transito,Em_Andamento,Passageiros\n";

    for (const auto& viagem : viagens) {
        arquivo << viagem.conversorCSV() << "\n";
    }

    arquivo.close();
    std::cout << "Viagens salvas com sucesso no arquivo viagens.csv!" << std::endl;
}

void Viagem::carregarViagens(std::vector<Viagem>& viagens, 
                             const std::vector<Cidade>& cidades, 
                             const std::vector<Transporte>& transportes) {
    std::ifstream arquivo("viagens.csv");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo viagens.csv!" << std::endl;
        return;
    }

    std::string linha;
    getline(arquivo, linha); // Ignorar o cabeçalho

    while (getline(arquivo, linha)) {
        std::istringstream iss(linha);
        std::string campo;

        // Transporte
        getline(iss, campo, ',');
        Transporte* transporte = nullptr;
        for (const auto& t : transportes) {
            if (t.getNome() == campo) {
                transporte = const_cast<Transporte*>(&t);
                break;
            }
        }

        // Origem
        getline(iss, campo, ',');
        Cidade* origem = nullptr;
        for (const auto& c : cidades) {
            if (c.getNome() == campo) {
                origem = const_cast<Cidade*>(&c);
                break;
            }
        }

        // Destino
        getline(iss, campo, ',');
        Cidade* destino = nullptr;
        for (const auto& c : cidades) {
            if (c.getNome() == campo) {
                destino = const_cast<Cidade*>(&c);
                break;
            }
        }

        // Próxima viagem (ignorar por enquanto)
        getline(iss, campo, ',');

        // Horas em trânsito
        getline(iss, campo, ',');
        int horasEmTransito = std::stoi(campo);

        // Status da viagem
        getline(iss, campo, ',');
        bool emAndamento = (campo == "true");

        // Passageiros
        getline(iss, campo, ',');
        std::vector<Passageiro*> passageiros;
        if (campo != "NULL") {
            std::istringstream issPassageiros(campo);
            std::string nomePassageiro;
            while (getline(issPassageiros, nomePassageiro, '|')) {
                passageiros.push_back(new Passageiro(nomePassageiro, origem));
            }
        }

        // Criar viagem e adicionar ao vetor
        Viagem viagem(transporte, passageiros, origem, destino, horasEmTransito, emAndamento);
        viagens.push_back(viagem);

    }

    arquivo.close();
    std::cout << "Viagens carregadas com sucesso do arquivo viagens.csv!" << std::endl;
}

bool Viagem::getStatus() const {
    return emAndamento;
}

void Viagem::setTempoRestante(int horas) {
    horasEmTransito = horas;
}

int Viagem::getTempoRestante() const {
    return horasEmTransito;
}

Transporte* Viagem::getTransporte() {
    return transporte;
}

void Viagem::setStatus(bool status) {
    emAndamento = status;
}

std::vector<Passageiro*> Viagem::getPassageiros() const {
    return passageiros;
}
