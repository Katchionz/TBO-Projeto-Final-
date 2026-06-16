#include <iostream>
#include "MenuMetodos.hpp"

using namespace std;

int main() {
    int opcao = -1;

    while (opcao != 0) {
        exibirMenu();
        
        // Proteção contra o usuário digitar letras em vez de números
        if (!(cin >> opcao)) {
            cout << "Entrada invalida. Encerrando o sistema." << endl;
            break;
        }

        switch (opcao) {
            case 1: executarBuscaKMP(); break;
            case 2: executarVerificacaoOrtografica(); break;
            case 3: executarSugestaoCorrecao(); break;
            case 4: executarQuebraCifra(); break;
            case 5: executarAnalisePerformance(); break;
            case 0: cout << "Sistema encerrado com sucesso." << endl; break;
            default: cout << "Opcao invalida. Tente novamente." << endl;
        }
    }

    return 0;
}