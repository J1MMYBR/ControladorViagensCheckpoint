#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include "utils.h"
#include "cidade.h"
#include "passageiro.h"
#include "trajeto.h"
#include "transporte.h"
#include "viagem.h"

using namespace std;

void menu(){
    cout << "\n====== Controlador de Viagens ======" << endl;
    cout << "1- Cadastro de Cidade" << endl;
    cout << "2 - Cadastro de Passageiro" << endl;
    cout << "3 - Cadastro de Trajeto" << endl;
    cout << "4 - Cadastro de Transporte" << endl;
    cout << "5 - Cadastro de Viagem" << endl;
    cout << "6 - Consultas e relatorios (Nao implementado ainda)" << endl;
    cout << "7 - Limpar terminal" << endl;
    cout << "8 - Sair" << endl;
    cout << "==============================\n";
}

int interacao(){
    int opcao;
    cout << "Digite sua opcao: \n";
    cin >> opcao; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer residual

    switch (opcao) {
    case 1: {
        cadastroCidade();
        break;
    }
    case 2: {
        cadastroPassageiro();
        break;
    }
    case 3: {
        cadastroTrajeto();
        break;
    }
    case 4: {
        cadastroTransporte();
        break;
    }
    case 5: {
        cadastroViagem();
        break;
    }
    case 6: {
        cout << "Calma um pouco, ainda nao foi implementado kk" << endl;
        break;
    }
    case 7: {
        system("cls");
        break;
    }
    case 8: {
        cout << endl << "Encerrando o programa." << endl;
        break;
    }
    default: {
        cout << endl << "Opcao invalida! escolha uma opcao disponivel." << endl;
        break;
    }
    }
    
    return opcao;
}

void criarArquivos() {
    std::ofstream arquivo;

    arquivo.open("cidades.csv", std::ios::app);
    if (!arquivo) {
        std::cerr << "Erro ao criar cidades.csv\n";
    } else {
        arquivo.seekp(0, std::ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Nome \n";
            std::cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        std::cout << "Arquivo cidades.csv verificado/criado.\n";
    }

    arquivo.open("passageiros.csv", std::ios::app);
    if (!arquivo) {
        std::cerr << "Erro ao criar passageiros.csv\n";
    } else {
        arquivo.seekp(0, std::ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Nome, Local_Atual \n";
            std::cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        std::cout << "Arquivo passageiros.csv verificado/criado.\n";
    }

    arquivo.open("trajetos.csv", std::ios::app);
    if (!arquivo) {
        std::cerr << "Erro ao criar trajetos.csv\n";
    } else {
        arquivo.seekp(0, std::ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Origem, Destino, Tipo, Distancia \n";
            std::cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        std::cout << "Arquivo trajetos.csv verificado/criado.\n";
    }

    arquivo.open("transportes.csv", std::ios::app);
    if (!arquivo) {
        std::cerr << "Erro ao criar transportes.csv\n";
    } else {
        arquivo.seekp(0, std::ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Nome, Tipo, Capacidade, Velocidade, Dist_Descanso, Tempo_Descanso, Local_Atual \n";
            std::cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        std::cout << "Arquivo transportes.csv verificado/criado.\n";
    }

    arquivo.open("viagens.csv", std::ios::app);
    if (!arquivo) {
        std::cerr << "Erro ao criar viagens.csv\n";
    } else {
        arquivo.seekp(0, std::ios::end);
        if (arquivo.tellp() == 0){
            arquivo << "Transporte, Origem, Destino, Proxima, Horas_Em_Transito, Em_Andamento \n";
            std::cout << "Arquivo criado!. \n";
        }
        arquivo.close();
        std::cout << "Arquivo viagens.csv verificado/criado.\n";
    }
}

void cadastroCidade(){
    string nome;
    cout << "Digite o nome da cidade que deseja cadastrar: ";
    cin >> nome;

    Cidade cidade(nome); // Atribui o nome da cidade fornecida pelo usuário à variável 'nome' da classe 'Cidade'

    if(cidade.getNome().empty()) // tratamento de erro para verificar se foi possível cadastrar a cidade
    { 
        cout << "Erro ao adicionar cidade. Tente novamente"<< endl;
    }
    else 
    {
        ofstream arqCidades("cidades.csv", ios::app); // abre o arquivo para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo

        if (!arqCidades) { // verificar se o arquivo foi aberto corretamente
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        arqCidades << cidade.getNome() << "\n";
        
        cout << "Cidade '"<< cidade.getNome() << "' adicionada com sucesso." << endl;

        arqCidades.close();
    }
}

void cadastroPassageiro() {
    string nome, localAtual;
    
    cout << "Digite o nome do passageiro: ";
    cin >> nome;

    cout << "Digite o nome da cidade atual do passageiro: ";
    cin >> localAtual;

    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;
    bool cidadeEncontrada = false;
    while (getline(arqCidades, linha)) {
        if (linha == localAtual) {
            cidadeEncontrada = true;
            break;
        }
    }

    if (!cidadeEncontrada) {
        cout << "A cidade '" << localAtual << "' não foi cadastrada. Cadastre-a primeiro." << endl;
        return;
    }

    Cidade* cidadeAtual = new Cidade(localAtual);
    Passageiro passageiro(nome, cidadeAtual);
    
    ofstream arqPassageiros("passageiros.csv", ios::app);
    if (!arqPassageiros) {
        cerr << "Erro ao abrir o arquivo 'passageiros.csv'." << endl;
        return;
    }

    cout << passageiro.getNome() << endl;

    arqPassageiros << nome << ", " << passageiro.getLocalAtual()->getNome() << "\n";

    
    cout << "Passageiro '" << nome << "' cadastrado com sucesso." << endl;

    arqPassageiros.close();
    
    delete cidadeAtual;
}

void cadastroTrajeto(){
    string origem, destino;
    char tipoTrajeto;
    int distancia;

    cout << "Digite o nome da cidade de origem do trajeto: ";
    cin >> origem;
    cout << "Digite o nome da cidade de destino do trajeto: ";
    cin >> destino;

    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;
    bool verificaOrigem = false;
    bool verificaDestino = false;

    while (getline(arqCidades, linha)) { // percorrer linha por linha no arquivo
        
        if (linha == origem) { // Verificar se a linha contém a cidade de origem
            verificaOrigem = true;
        }

        if (linha == destino) { // Verificar se a linha contém a cidade de destino
            verificaDestino = true;
        }

        if(verificaOrigem == true && verificaDestino == true){
            break;
        }
    }

    if(verificaOrigem == false){
        
        cout << "A cidade de origem '" << origem << "' nao foi cadastrada. Escolha outra cidade ou cadastre-a." << endl;

        return;
    }

    if(verificaDestino == false){
        
        cout << "A cidade de destino '" << destino << "' nao foi cadastrada. Escolha outra cidade ou cadastre-a." << endl;

        return;
    }

        cout << endl << "Digite o tipo do trajeto ('A' para aquatico e 'T' para terrestre): ";
        cin >> tipoTrajeto;
        tipoTrajeto = toupper(tipoTrajeto);
    
    while(true){
        if(tipoTrajeto == 'A' || tipoTrajeto == 'T'){
            break;
        }else{
            cout << endl << "Tipo invalido" << endl;
            cout << "Digite o tipo do trajeto ('A' para aquatico e 'T' para terrestre): ";
            cin >> tipoTrajeto;
            tipoTrajeto = toupper(tipoTrajeto);
        }
    }
    
    do
    {   
        if(distancia<= 0){
            cout << endl << "Distancia invalida" << endl;
        }
        cout << "Digite a distancia do trajeto (em km): ";
        cin >> distancia;
    } while (distancia <= 0);

    Cidade origemA_obj(origem); // Cria a instância da cidade de origem
    Cidade destinoA_obj(destino); // Cria a instância da cidade de destino
    Cidade* origemA = &origemA_obj; // Ponteiro para a cidade de origem
    Cidade* destinoA = &destinoA_obj; // Ponteiro para a cidade de destino
    Trajeto trajeto(origemA, destinoA, tipoTrajeto, distancia); // Criação do trajeto

    if(trajeto.getOrigem()->getNome().empty() || trajeto.getDestino()->getNome().empty()) // tratamento de erro para verificar se foi possível cadastrar o trajeto
    { 
        
        cout << "Erro ao cadastrar trajeto. Tente novamente"<< endl;
    }
    else 
    {
        ofstream arqTrajeto("trajetos.csv", ios::app); // abre o arquivo para escrita - 'ios::app' permite que linhas sejam adicionadas ao invés de sobrescrever o conteúdo do arquivo

        if (!arqCidades) { // verificar se o arquivo foi aberto corretamente
            cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        // Adiciona trajeto para linha do arquivo "trajeto.csv"
        arqTrajeto << trajeto.getOrigem()->getNome() << "," << trajeto.getDestino()->getNome() << "," << trajeto.getTipoTrajeto() << "," << trajeto.getDistancia() << "\n";

        
        cout << "Trajeto de '"<< trajeto.getOrigem()->getNome() << "' para '" << trajeto.getDestino()->getNome() << "' adicionado com sucesso." << endl;

        arqTrajeto.close();
    }
}

void cadastroTransporte() {
    string nome;
    char tipoTransporte;
    int capacidade, velocidade, distanciaDescanso, tempoDescanso;
    string localAtual;

    cout << "Digite o nome do transporte: ";
    cin >> nome;

    cout << "Digite o tipo de transporte ('A' para aquático, 'T' para terrestre): ";
    cin >> tipoTransporte;
    tipoTransporte = toupper(tipoTransporte);
    
    while(tipoTransporte != 'A' && tipoTransporte != 'T') {
        cout << "Tipo invalido. Digite 'A' para aquático ou 'T' para terrestre: ";
        cin >> tipoTransporte;
        tipoTransporte = toupper(tipoTransporte);
    }
    
    cout << "Digite a capacidade de passageiros: ";
    cin >> capacidade;

    cout << "Digite a velocidade do transporte (km/h): ";
    cin >> velocidade;

    cout << "Digite a distância de descanso (km): ";
    cin >> distanciaDescanso;

    cout << "Digite o tempo de descanso (horas): ";
    cin >> tempoDescanso;
    
    cin.ignore();
    
    cout << "Digite o nome da cidade atual do transporte: ";
    cin >> localAtual;

    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'" << endl;
        return;
    }

    string linha;
    bool cidadeEncontrada = false;
    while (getline(arqCidades, linha)) {
        if (linha == localAtual) {
            cidadeEncontrada = true;
            break;
        }
    }

    if (!cidadeEncontrada) {
        
        cout << "A cidade '" << localAtual << "' não foi cadastrada. Cadastre-a primeiro." << endl;
        return;
    }

    Cidade cidade(localAtual);
    Transporte transporte(nome, tipoTransporte, capacidade, velocidade, distanciaDescanso, tempoDescanso, &cidade);
    
    ofstream arqTransportes("transportes.csv", ios::app);
    if (!arqTransportes) {
        cerr << "Erro ao abrir o arquivo 'transportes.csv'." << endl;
        return;
    }

    arqTransportes << nome << "," << tipoTransporte << "," << capacidade << "," << velocidade << "," << distanciaDescanso << "," << tempoDescanso << "," << localAtual << "\n";

    cout << "Transporte '" << nome << "' cadastrado com sucesso." << endl;

    arqTransportes.close();
}

void cadastroViagem() {
    string nomeTransporte, origem, destino;
    
    cout << "Digite o nome do transporte: ";
    cin >> nomeTransporte;

    cout << "Digite a cidade de origem: ";
    cin >> origem;

    cout << "Digite a cidade de destino: ";
    cin >> destino;

    ifstream arqCidades("cidades.csv");
    if (!arqCidades.is_open()) {
        cerr << "Erro ao abrir o arquivo 'cidades.csv'." << endl;
        return;
    }

    string linha;
    bool origemEncontrada = false, destinoEncontrado = false;
    while (getline(arqCidades, linha)) {
        if (linha == origem) origemEncontrada = true;
        if (linha == destino) destinoEncontrado = true;
        if (origemEncontrada && destinoEncontrado) break;
    }

    if (!origemEncontrada) {
        
        cout << "A cidade de origem '" << origem << "' não foi cadastrada. Cadastre-a primeiro." << endl;
        return;
    }

    if (!destinoEncontrado) {
        
        cout << "A cidade de destino '" << destino << "' não foi cadastrada. Cadastre-a primeiro." << endl;
        return;
    }

    Cidade cidadeOrigem(origem);
    Cidade cidadeDestino(destino);
    
    ifstream arqTransportes("transportes.csv");
    if (!arqTransportes.is_open()) {
        cerr << "Erro ao abrir o arquivo 'transportes.csv'." << endl;
        return;
    }

    bool transporteEncontrado = false;
    while (getline(arqTransportes, linha)) {
        if (linha.find(nomeTransporte) != string::npos) {
            transporteEncontrado = true;
            break;
        }
    }

    if (!transporteEncontrado) {
        
        cout << "O transporte '" << nomeTransporte << "' não foi cadastrado. Cadastre-o primeiro." << endl;
        return;
    }

    Transporte transporte(nomeTransporte, 'T', 0, 0, 0, 0, &cidadeOrigem);
    vector<Passageiro*> passageiros;
    
    Viagem viagem(&transporte, passageiros, &cidadeOrigem, &cidadeDestino);
    
    ofstream arqViagens("viagens.csv", ios::app);
    if (!arqViagens) {
        cerr << "Erro ao abrir o arquivo 'viagens.csv'." << endl;
        return;
    }

    arqViagens << nomeTransporte << "," << origem << "," << destino << "," << "\n";

    
    cout << "Viagem de '" << origem << "' para '" << destino << "' cadastrada com sucesso." << endl;

    arqViagens.close();
}
