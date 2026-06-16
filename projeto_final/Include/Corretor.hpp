#ifndef CORRETOR_HPP
#define CORRETOR_HPP

#include <string>
#include <vector>

struct Sugestao {
    int distancia;
    std::string palavra;
};

class Corretor {
private:
    std::vector<std::string> dicionario;

    // Função auxiliar para achar o mínimo entre três números sem usar std::min
    int minimo3(int a, int b, int c);
    
    // Algoritmo de Programação Dinâmica (Levenshtein)
    int calcularDistancia(const std::string& s1, const std::string& s2);

public:
    void carregarDicionario(const std::string& caminhoArquivo);
    std::vector<std::string> sugerir(const std::string& palavraErrada, int limite = 3);

};

#endif
