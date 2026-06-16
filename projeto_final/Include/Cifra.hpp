#ifndef CIFRA_HPP
#define CIFRA_HPP

#include <string>
#include <vector>

class Cifra {
private:
    std::vector<std::string> dicionario;

    // Algoritmos de Ordenação e Busca criados do zero
    void ordenarDicionario(int esq, int dir);
    bool buscaBinaria(const std::string& palavra);
    int contarPalavrasValidas(const std::string& texto);

public:
    void carregarEOrdenarDicionario(const std::string& caminhoArquivo);
    std::string cifrar(const std::string& texto, int chave);
    std::string decifrar(const std::string& texto, int chave);
    void quebrarCifra(const std::string& textoCifrado);
};

#endif