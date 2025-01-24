#include <iostream>
#include <limits>
#include "controlador.h"

using namespace std;

// Exibe o menu de opções
void menu() {
    cout << "\n====== Controlador de Viagens ======" << endl;
    cout << "1 - Cadastro de Cidade" << endl;
    cout << "2 - Cadastrar Trajeto" << endl;
    cout << "3 - Cadastro de Transporte" << endl;
    cout << "4 - Cadastro de Passageiro" << endl;
    cout << "5 - Iniciar Viagem" << endl;
    cout << "6 - Avançar Horas" << endl;
    cout << "7 - Relatar Estado" << endl;
    cout << "8 - Limpar terminal" << endl;
    cout << "9 - Sair" << endl;
    cout << "==============================" << endl;
    cout << "Escolha uma opcao: ";
}

// Processa a interação do usuário
void interacao(ControladorDeTransito& controlador) {
    int opcao = 0;

    do {
        menu();
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer do `cin`

        switch (opcao) {
        case 1: {
            string nomeCidade;
            int indice;
            cout << "Digite o nome da cidade: ";
            getline(cin, nomeCidade);
            cout << "Digite o indice da cidade: ";
            cin >> indice;
            controlador.cadastrarCidade(nomeCidade, indice);
            break;
        }
        case 2: {
            string origem, destino;
            char tipo;
            int distancia;

            cout << "Digite o nome da cidade de origem: ";
            getline(cin, origem);
            cout << "Digite o nome da cidade de destino: ";
            getline(cin, destino);
            cout << "Digite o tipo do trajeto ('T' para terrestre, 'A' para aquatico): ";
            cin >> tipo;
            cout << "Digite a distancia do trajeto (em km): ";
            cin >> distancia;
            cin.ignore();

            controlador.cadastrarTrajeto(origem, destino, tipo, distancia);
            break;
        }
        case 3: {
            string nome, localAtual;
            char tipo;
            int capacidade, velocidade, distanciaDescanso, tempoDescanso;

            cout << "Digite o nome do transporte: ";
            getline(cin, nome);
            cout << "Digite o tipo do transporte ('T' para terrestre, 'A' para aquatico): ";
            cin >> tipo;
            cout << "Digite a capacidade do transporte: ";
            cin >> capacidade;
            cout << "Digite a velocidade do transporte (em km/h): ";
            cin >> velocidade;
            cout << "Digite a distancia de descanso do transporte (em km): ";
            cin >> distanciaDescanso;
            cout << "Digite o tempo de descanso do transporte (em horas): ";
            cin >> tempoDescanso;
            cin.ignore();
            cout << "Digite a cidade atual do transporte: ";
            getline(cin, localAtual);

            controlador.cadastrarTransporte(nome, tipo, capacidade, velocidade, distanciaDescanso, tempoDescanso, localAtual);
            break;
        }
        case 4: {
            string nome, localAtual;

            cout << "Digite o nome do passageiro: ";
            getline(cin, nome);
            cout << "Digite a cidade atual do passageiro: ";
            getline(cin, localAtual);

            controlador.cadastrarPassageiro(nome, localAtual);
            break;
        }
        case 5: {
            string nomeTransporte, origem, destino;
            int qtdPassageiros;
            vector<string> nomesPassageiros;

            cout << "Digite o nome do transporte: ";
            getline(cin, nomeTransporte);
            cout << "Digite a cidade de origem: ";
            getline(cin, origem);
            cout << "Digite a cidade de destino: ";
            getline(cin, destino);
            cout << "Digite o numero de passageiros: ";
            cin >> qtdPassageiros;
            cin.ignore();

            for (int i = 0; i < qtdPassageiros; ++i) {
                string nomePassageiro;
                cout << "Digite o nome do passageiro " << i + 1 << ": ";
                getline(cin, nomePassageiro);
                nomesPassageiros.push_back(nomePassageiro);
            }

            controlador.iniciarViagem(nomeTransporte, nomesPassageiros, origem, destino);
            break;
        }
        case 6: { // Avançar horas
            int horas;
            std::cout << "Digite a quantidade de horas a avançar: ";
            std::cin >> horas;
            controlador.avancarTempo(horas);
            break;
        }
        case 7: {
            controlador.relatarEstado();
            break;
        }
        case 8:
        #if _WIN32 || _WIN64
            system("cls");
        #else
            system("clear");
        #endif
        case 9:
            cout << "Encerrando o programa...\n";
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 9);

    return;
}

void criarArquivos() {
    ofstream arquivo;

    arquivo.open("cidades.csv", ios::app);
    if (!arquivo) {
        cerr << "Erro ao criar cidades.csv\n";
    } else {
        arquivo.seekp(0, ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Nome \n";
            cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        cout << "Arquivo cidades.csv verificado/criado.\n";
    }

    arquivo.open("passageiros.csv", ios::app);
    if (!arquivo) {
        cerr << "Erro ao criar passageiros.csv\n";
    } else {
        arquivo.seekp(0, ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Nome, Local_Atual \n";
            cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        cout << "Arquivo passageiros.csv verificado/criado.\n";
    }

    arquivo.open("trajetos.csv", ios::app);
    if (!arquivo) {
        cerr << "Erro ao criar trajetos.csv\n";
    } else {
        arquivo.seekp(0, ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Origem, Destino, Tipo, Distancia \n";
            cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        cout << "Arquivo trajetos.csv verificado/criado.\n";
    }

    arquivo.open("transportes.csv", ios::app);
    if (!arquivo) {
        cerr << "Erro ao criar transportes.csv\n";
    } else {
        arquivo.seekp(0, ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Nome, Tipo, Capacidade, Velocidade, Dist_Descanso, Tempo_Descanso, Local_Atual \n";
            cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        cout << "Arquivo transportes.csv verificado/criado.\n";
    }

    arquivo.open("viagens.csv", ios::app);
    if (!arquivo) {
        cerr << "Erro ao criar viagens.csv\n";
    } else {
        arquivo.seekp(0, ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Transporte, Origem, Destino \n";
            cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        cout << "Arquivo viagens.csv verificado/criado.\n";
    }
}
