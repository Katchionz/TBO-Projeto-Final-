#include "MenuMetodos.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

// Importando os cabeçalhos dos algoritmos
#include "KMP.hpp"
#include "Dicionario.hpp"
#include "Corretor.hpp"
#include "Cifra.hpp"
#include "Buscador.hpp"

using namespace std;
using namespace std::chrono;

void exibirMenu() {
    cout << "\n=======================================================" << endl;
    cout << "          MENU INTERATIVO - PROJETO FINAL TBO          " << endl;
    cout << "=======================================================" << endl;
    cout << "[1] Busca Exata em Dicionario (KMP Original)" << endl;
    cout << "[2] Verificacao Ortografica Completa (Trie)" << endl;
    cout << "[3] Sugestao de Correcao Ortografica (Levenshtein)" << endl;
    cout << "[4] Criptografia: Cifrar e Quebrar Cifra" << endl;
    cout << "[5] Analise Comparativa de Performance" << endl;
    cout << "[0] Sair do Sistema" << endl;
    cout << "=======================================================" << endl;
    cout << "Escolha a opcao desejada: ";
}

void executarBuscaKMP() {
    cout << "\n--- [1] BUSCA KMP ORIGINAL ---" << endl;
    ifstream arquivoDicionario("Base de dados/dicionario.txt");
    if (!arquivoDicionario.is_open()) {
        cout << "Erro: Arquivo dicionario.txt nao encontrado!" << endl;
        return;
    }
    stringstream buffer;
    buffer << arquivoDicionario.rdbuf();
    arquivoDicionario.close();
    
    string palavraBusca;
    cout << "Digite a palavra que deseja buscar: ";
    cin >> palavraBusca;

    buscaKMP_Original(buffer.str(), palavraBusca);
}

void executarVerificacaoOrtografica() {
    cout << "\n--- [2] VERIFICACAO ORTOGRAFICA (TRIE) ---" << endl;
    Dicionario dict;
    ifstream arquivoDict("Base de dados/words.txt");
    if (!arquivoDict.is_open()) return;
    
    string palavra;
    while (arquivoDict >> palavra) dict.inserir(palavra);
    arquivoDict.close();

    int op;
    cout << "Escolha o arquivo (1- Correto | 2- Com Erro): ";
    cin >> op;
    string caminho = (op == 1) ? "Base de dados/texto_teste_correto.txt" : "Base de dados/texto_teste_com_erro.txt";

    ifstream arquivoTexto(caminho);
    if (!arquivoTexto.is_open()) return;

    string token;
    bool semErros = true;
    while (arquivoTexto >> token) {
        if (!dict.buscar(token)) {
            cout << "[ERRO]: " << token << endl;
            semErros = false;
        }
    }
    if (semErros) cout << "Nenhum erro encontrado!" << endl;
}

void executarSugestaoCorrecao() {
    cout << "\n--- [3] SUGESTAO DE CORRECAO (LEVENSHTEIN) ---" << endl;
    Corretor corretor;
    corretor.carregarDicionario("Base de dados/words.txt");

    string palavraErrada;
    cout << "Digite uma palavra errada: ";
    cin >> palavraErrada;

    vector<string> sugestoes = corretor.sugerir(palavraErrada, 3);
    cout << "\nVoce quis dizer:" << endl;
    for (size_t i = 0; i < sugestoes.size(); i++) {
        cout << i + 1 << ". " << sugestoes[i] << endl;
    }
}

void executarQuebraCifra() {
    cout << "\n--- [4] CRIPTOGRAFIA E QUEBRA DA CIFRA ---" << endl;
    Cifra enigma;
    enigma.carregarEOrdenarDicionario("Base de dados/words.txt");

    string textoOriginal = "projeto de estrutura finalizado com sucesso";
    string textoCifrado = enigma.cifrar(textoOriginal, 7);
    
    cout << "Mensagem Cifrada: " << textoCifrado << endl;
    cout << "Iniciando quebra por forca bruta..." << endl;
    enigma.quebrarCifra(textoCifrado);
}

void executarAnalisePerformance() {
    cout << "\n--- [5] ANALISE DE PERFORMANCE ---" << endl;
    Buscador analisador;
    vector<string> alvos = {"algoritmo", "dados", "memoria", "ponteiros", "estrutura"};
    analisador.carregarPadroes(alvos);

    ifstream arquivoLongo("Base de dados/texto_teste_3.txt");
    stringstream strBuf;
    strBuf << arquivoLongo.rdbuf();
    string massaDados = strBuf.str();
    
    analisador.construirAhoCorasick();
    
    auto start = high_resolution_clock::now();
    int oAC = analisador.buscaAhoCorasick(massaDados);
    auto tAC = duration_cast<microseconds>(high_resolution_clock::now() - start).count();

    start = high_resolution_clock::now();
    int oKMP = analisador.buscaKMP(massaDados);
    auto tKMP = duration_cast<microseconds>(high_resolution_clock::now() - start).count();

    start = high_resolution_clock::now();
    int oIng = analisador.buscaIngenua(massaDados);
    auto tIng = duration_cast<microseconds>(high_resolution_clock::now() - start).count();

    cout << "\n1. Aho-Corasick: " << oAC << " ocorrencias | " << tAC << " us" << endl;
    cout << "2. Busca KMP:    " << oKMP << " ocorrencias | " << tKMP << " us" << endl;
    cout << "3. B. Ingenua:   " << oIng << " ocorrencias | " << tIng << " us" << endl;
}