#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    int opcao = 0;
    criarArquivos();

    do {
        menu();
        opcao = interacao();
    } while (opcao != 8);

    return 0;
}