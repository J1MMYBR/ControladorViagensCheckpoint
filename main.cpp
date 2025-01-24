#include <iostream>
#include "utils.h"
#include "controlador.h"

using namespace std;

int main() {
    ControladorDeTransito controlador;
    criarArquivos();

    interacao(controlador);

    return 0;
}