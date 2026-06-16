#include "Corretor.hpp"
#include <fstream>
#include <iostream>

int Corretor::minimo3(int a, int b, int c) {
    int menor = a;
    if (b < menor) menor = b;
    if (c < menor) menor = c;
    return menor;
}

int Corretor::calcularDistancia(const std::string& s1, const std::string& s2) {
    int len1 = s1.size();
    int len2 = s2.size();
    std::vector<std::vector<int>> matriz(len1 + 1, std::vector<int>(len2 + 1));

    for (int i = 0; i <= len1; i++) matriz[i][0] = i;
    for (int j = 0; j <= len2; j++) matriz[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int custoSubstituicao = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            matriz[i][j] = minimo3(
                matriz[i - 1][j] + 1,                 // Deleção
                matriz[i][j - 1] + 1,                 // Inserção
                matriz[i - 1][j - 1] + custoSubstituicao // Substituição
            );
        }
    }
    return matriz[len1][len2];
}

void Corretor::carregarDicionario(const std::string& caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    std::string palavra;
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir dicionario para o corretor." << std::endl;
        return;
    }
    while (arquivo >> palavra) {
        dicionario.push_back(palavra);
    }
    arquivo.close();
    
}

std::vector<std::string> Corretor::sugerir(const std::string& palavraErrada, int limite) {
    // Inicializa o vetor de sugestões com distâncias "infinitas"
    std::vector<Sugestao> top(limite, {999999, ""});

    for (const std::string& palavraDict : dicionario) {
        int dist = calcularDistancia(palavraErrada, palavraDict);

        // Se a distância for menor que a pior do nosso Top N, nós a inserimos
        if (dist < top.back().distancia) {
            top.back() = {dist, palavraDict};
            
            // "Bubble sort" manual apenas no pequeno array de 3 posições
            for (int i = limite - 1; i > 0; i--) {
                if (top[i].distancia < top[i-1].distancia) {
                    Sugestao temp = top[i];
                    top[i] = top[i-1];
                    top[i-1] = temp;
                }
            }
        }
    }

    std::vector<std::string> resultado;
    for (const auto& sug : top) {
        if (sug.distancia != 999999) resultado.push_back(sug.palavra);
    }
    return resultado;
}
