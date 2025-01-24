#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#include <unordered_map>
#include "controlador.h"

using namespace std;

ControladorDeTransito::ControladorDeTransito() {}

pair<vector<int>, vector<int>> ControladorDeTransito::dijkstra(int origem, const vector<vector<Edge>>& grafo) {
    int n = grafo.size();
    vector<int> distancias(n, INT_MAX);
    vector<int> antecessor(n, -1);
    distancias[origem] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, origem});

    while (!pq.empty()) {
        int distanciaAtual = pq.top().first;
        int cidadeAtual = pq.top().second;
        pq.pop();

        if (distanciaAtual > distancias[cidadeAtual]) continue;

        for (const Edge& vizinho : grafo[cidadeAtual]) {
            int novaDistancia = distanciaAtual + vizinho.distancia;

            if (novaDistancia < distancias[vizinho.destino]) {
                distancias[vizinho.destino] = novaDistancia;
                antecessor[vizinho.destino] = cidadeAtual;
                pq.push({novaDistancia, vizinho.destino});
            }
        }
    }

    return {distancias, antecessor};
}

vector<int> ControladorDeTransito::reconstruirCaminho(int origem, int destino, const vector<int>& antecessor) {
    vector<int> caminho;
    for (int at = destino; at != -1; at = antecessor[at]) {
        caminho.push_back(at);
        if (at == origem) break;
    }
    reverse(caminho.begin(), caminho.end());
    return caminho;
}

pair<list<Cidade*>, int> ControladorDeTransito::calcularMelhorRota(Cidade& origem, Cidade& destino, char tipo) {
    vector<vector<Edge>> grafo(cidades.size() + 1);

    for (auto& trajeto : trajetos) {
        if (trajeto->getTipoTrajeto() == tipo) {
            grafo[trajeto->getOrigem()->getIndice()].push_back({trajeto->getDestino()->getIndice(), trajeto->getDistancia()});
            grafo[trajeto->getDestino()->getIndice()].push_back({trajeto->getOrigem()->getIndice(), trajeto->getDistancia()});
        }
    }

    auto resultado = dijkstra(origem.getIndice(), grafo);
    auto distancias = resultado.first;
    auto antecessores = resultado.second;

    if (distancias[destino.getIndice()] == INT_MAX) {
        cout << "Não há caminho entre as cidades informadas.\n";
        return {{}, 0};
    }

    auto caminho = reconstruirCaminho(origem.getIndice(), destino.getIndice(), antecessores);

    list<Cidade*> cidadesVisitadas;
    for (int idx : caminho) {
        for (auto& cidade : cidades) {
            if (cidade->getIndice() == idx) {
                cidadesVisitadas.push_back(cidade);
                break;
            }
        }
    }

    return {cidadesVisitadas, distancias[destino.getIndice()]};
}

Cidade* ControladorDeTransito::buscarCidade(const string& nome) {
    for (auto& cidade : cidades) {
        if (cidade->getNome() == nome) return cidade;
    }
    return nullptr;
}

Transporte* ControladorDeTransito::buscarTransporte(const string& nome) {
    for (auto& transporte : transportes) {
        if (transporte->getNome() == nome) return transporte;
    }
    return nullptr;
}

Passageiro* ControladorDeTransito::buscarPassageiro(const string& nome) {
    for (auto& passageiro : passageiros) {
        if (passageiro->getNome() == nome) return passageiro;
    }
    return nullptr;
}

Trajeto* ControladorDeTransito::buscarTrajeto(Cidade* origem, Cidade* destino) {
    for (auto& trajeto : trajetos) {
        if (trajeto->getOrigem() == origem && trajeto->getDestino() == destino) return trajeto;
    }
    return nullptr;
}

void ControladorDeTransito::avancarTempo(int horas) {
    tempoCorrido += horas;

    for (auto& viagem : viagens) {
        if (viagem->getStatus()) {
            viagem->setTempoRestante(viagem->getTempoRestante() - horas);

            int distanciaPercorrida = horas * viagem->getTransporte()->getVelocidade();

            if (distanciaPercorrida >= viagem->getTransporte()->getDistanciaDescanso()) {
                int paradas = distanciaPercorrida / viagem->getTransporte()->getDistanciaDescanso();
                viagem->setTempoRestante(viagem->getTempoRestante() + paradas * viagem->getTransporte()->getTempoDescanso());
            }

            if (viagem->getTempoRestante() <= 0) {
                finalizarViagem(viagem);
            }
        }
    }
}

void ControladorDeTransito::finalizarViagem(Viagem* viagem) {
    viagem->setStatus(false);

    for (auto& passageiro : viagem->getPassageiros()) {
        passageiro->setLocalAtual(viagem->getDestino());
    }

    viagem->getTransporte()->setLocalAtual(viagem->getDestino());

    cout << "Viagem de " << viagem->getOrigem()->getNome() << " para " << viagem->getDestino()->getNome() << " finalizada com sucesso.\n";
}

void ControladorDeTransito::cadastrarCidade(const string& nome, const int indice) {
    if (buscarCidade(nome)) {
        cout << "A cidade '" << nome << "' já foi cadastrada.\n";
        return;
    }
    cidades.push_back(new Cidade(nome, indice));
    cout << "Cidade '" << nome << "' cadastrada com sucesso.\n";

    Cidade cidade(nome, indice); 

    if(cidade.getNome().empty()) 
    { 
        cout << "Erro ao adicionar cidade. Tente novamente"<< endl;
    }
    else 
    {
        ofstream arqCidades("cidades.csv", ios::app); 

        if (!arqCidades) { 
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        arqCidades << cidade.getNome() << ", " << cidade.getIndice() << "\n";
        
        cout << "Cidade '"<< cidade.getNome() << "' adicionada com sucesso." << endl;

        arqCidades.close();
    }
}

void ControladorDeTransito::cadastrarTrajeto(const string& nomeOrigem, const string& nomeDestino, char tipo, int distancia) {
    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;
    int indiceOrigem = -1, indiceDestino = -1;

    while (getline(arqCidades, linha)) {
        size_t separador = linha.find(","); 
        if (separador != string::npos) {
            string nomeCidade = linha.substr(0, separador);
            string indiceStr = linha.substr(separador + 1);

            try {
                int indice = stoi(indiceStr); 

                if (nomeCidade == nomeOrigem) {
                    indiceOrigem = indice;
                }

                if (nomeCidade == nomeDestino) {
                    indiceDestino = indice;
                }

                if (indiceOrigem != -1 && indiceDestino != -1) {
                    break; 
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Erro: indice inválido no arquivo para a linha: " << linha << endl;
            } catch (const std::out_of_range& e) {
                cerr << "Erro: indice fora do intervalo permitido na linha: " << linha << endl;
            }
        } else {
            cerr << "Erro: linha malformada no arquivo: " << linha << endl;
        }
    }

    arqCidades.close();

    if (indiceOrigem == -1) {
        cout << "A cidade de origem '" << nomeOrigem << "' não foi encontrada no arquivo 'cidades.csv'. Cadastre-a primeiro." << endl;
        return;
    }

    if (indiceDestino == -1) {
        cout << "A cidade de destino '" << nomeDestino << "' não foi encontrada no arquivo 'cidades.csv'. Cadastre-a primeiro." << endl;
        return;
    }

    cout << "Digite o tipo do trajeto ('A' para aquático e 'T' para terrestre): ";
    cin >> tipo;
    tipo = toupper(tipo);
    while (tipo != 'A' && tipo != 'T') {
        cout << "Tipo inválido. Digite 'A' para aquático ou 'T' para terrestre: ";
        cin >> tipo;
        tipo = toupper(tipo);
    }

    while (distancia <= 0) {
        cout << "Distância inválida. Digite a distância do trajeto (em km): ";
        cin >> distancia;
    }

    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);
    if (!origem) {
        origem = new Cidade(nomeOrigem, indiceOrigem);
        cidades.push_back(origem); 
    }
    if (!destino) {
        destino = new Cidade(nomeDestino, indiceDestino);
        cidades.push_back(destino);
    }

    Trajeto* trajeto = new Trajeto(origem, destino, tipo, distancia);
    trajetos.push_back(trajeto);

    ofstream arqTrajetos("trajetos.csv", ios::app);
    if (!arqTrajetos.is_open()) {
        cerr << "Erro ao abrir o arquivo 'trajetos.csv'." << endl;
        return;
    }

    arqTrajetos << indiceOrigem << "," << nomeOrigem << ","
                << indiceDestino << "," << nomeDestino << ","
                << tipo << "," << distancia << "\n";

    arqTrajetos.close();

    cout << "Trajeto de '" << nomeOrigem << "' para '" << nomeDestino << "' cadastrado com sucesso no sistema e salvo no arquivo.\n";
}

void ControladorDeTransito::cadastrarTransporte(const string& nome, char tipo, int capacidade, int velocidade, int distanciaDescanso, int tempoDescanso, const string& localAtual) {
    Cidade* cidade = buscarCidade(localAtual);
    if (!cidade) {
        cout << "A cidade '" << localAtual << "' não foi cadastrada.\n";
        return;
    }

    Transporte* transporte = new Transporte(nome, tipo, capacidade, velocidade, distanciaDescanso, tempoDescanso, cidade);
    transportes.push_back(transporte);

    ofstream arqTransportes("transportes.csv", ios::app);
    if (!arqTransportes.is_open()) {
        cerr << "Erro ao abrir o arquivo 'transportes.csv'." << endl;
        return;
    }

    arqTransportes << nome << "," << tipo << "," << capacidade << "," << velocidade << ","
                   << distanciaDescanso << "," << tempoDescanso << "," << cidade->getIndice() << "," << cidade->getNome() << "\n";

    arqTransportes.close();

    cout << "Transporte '" << nome << "' cadastrado com sucesso no sistema e salvo no arquivo." << endl;
}


void ControladorDeTransito::cadastrarPassageiro(const string& nome, const string& localAtual) {
    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;
    int cidadeIndice = -1;
    bool cidadeEncontrada = false;

    while (getline(arqCidades, linha)) {
        size_t separador = linha.find(","); 
        if (separador != string::npos) {
            string nomeCidade = linha.substr(0, separador); 
            string indiceStr = linha.substr(separador + 1); 

            try {
                int indice = stoi(indiceStr); 

                if (nomeCidade == localAtual) {
                    cidadeIndice = indice; 
                    cidadeEncontrada = true;
                    break; 
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Erro: indice invalido no arquivo para a linha: " << linha << endl;
            } catch (const std::out_of_range& e) {
                cerr << "Erro: indice fora do intervalo permitido na linha: " << linha << endl;
            }
        } else {
            cerr << "Erro: linha malformada no arquivo: " << linha << endl;
        }
    }


    arqCidades.close();

    if (!cidadeEncontrada) {
        cout << "A cidade '" << localAtual << "' não foi encontrada no arquivo 'cidades.csv'. Cadastre-a primeiro." << endl;
        return;
    }

    Cidade* cidadeAtual = buscarCidade(localAtual);
    if (!cidadeAtual) {
        cidadeAtual = new Cidade(localAtual, cidadeIndice);
        cidades.push_back(cidadeAtual);
    }

    Passageiro* passageiro = new Passageiro(nome, cidadeAtual);
    passageiros.push_back(passageiro);

    ofstream arqPassageiros("passageiros.csv", ios::app);
    if (!arqPassageiros) {
        cerr << "Erro ao abrir o arquivo 'passageiros.csv'." << endl;
        delete passageiro;
        return;
    }

    arqPassageiros << passageiro->getNome() << ", " << passageiro->getLocalAtual()->getNome() << ", " << cidadeIndice << "\n";
    arqPassageiros.close();

    cout << "Passageiro '" << nome << "' cadastrado com sucesso.\n";
}

void ControladorDeTransito::iniciarViagem(const string& nomeTransporte, const vector<string>& nomesPassageiros, const string& nomeOrigem, const string& nomeDestino) {
    Transporte* transporte = buscarTransporte(nomeTransporte);
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);

    if (!transporte) {
        cout << "O transporte '" << nomeTransporte << "' não foi encontrado. Cadastre-o primeiro.\n";
        return;
    }

    if (!origem) {
        cout << "A cidade de origem '" << nomeOrigem << "' não foi encontrada. Cadastre-a primeiro.\n";
        return;
    }

    if (!destino) {
        cout << "A cidade de destino '" << nomeDestino << "' não foi encontrada. Cadastre-a primeiro.\n";
        return;
    }

    vector<Passageiro*> passageirosSelecionados;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* passageiro = buscarPassageiro(nome);
        if (passageiro) {
            passageirosSelecionados.push_back(passageiro);
        } else {
            cout << "Passageiro '" << nome << "' não encontrado. Ignorando...\n";
        }
    }

    if (passageirosSelecionados.empty()) {
        cout << "Nenhum passageiro válido foi selecionado para a viagem.\n";
        return;
    }

    Viagem* viagem = new Viagem(transporte, passageirosSelecionados, origem, destino, 0, true);
    viagens.push_back(viagem);

    cout << "Viagem de '" << nomeOrigem << "' para '" << nomeDestino << "' iniciada com sucesso.\n";

    ofstream arqViagens("viagens.csv", ios::app);
    if (!arqViagens.is_open()) {
        cerr << "Erro ao abrir o arquivo 'viagens.csv'.\n";
        return;
    }

    arqViagens << nomeTransporte << ",";
    for (size_t i = 0; i < passageirosSelecionados.size(); i++) {
        arqViagens << passageirosSelecionados[i]->getNome();
        if (i < passageirosSelecionados.size() - 1) arqViagens << "|"; 
    }
    arqViagens << "," << nomeOrigem << "," << nomeDestino << "\n";

    arqViagens.close();

    cout << "Viagem registrada no sistema e salva em 'viagens.csv'.\n";
}

void ControladorDeTransito::relatarEstado() {
    for (const auto& viagem : viagens) {
        viagem->relatarEstado();
    }
}