#include "Cifra.hpp"
#include <fstream>
#include <iostream>
#include <cctype>

// --- ALGORITMOS DE BASE (SEM USAR A BIBLIOTECA PADRÃO) ---

void Cifra::ordenarDicionario(int esq, int dir) {
    if (esq >= dir) return;
    int meio = esq + (dir - esq) / 2;
    ordenarDicionario(esq, meio);
    ordenarDicionario(meio + 1, dir);
    
    std::vector<std::string> temp;
    int i = esq, j = meio + 1;
    while (i <= meio && j <= dir) {
        if (dicionario[i] <= dicionario[j]) temp.push_back(dicionario[i++]);
        else temp.push_back(dicionario[j++]);
    }
    while (i <= meio) temp.push_back(dicionario[i++]);
    while (j <= dir) temp.push_back(dicionario[j++]);
    
    for (int k = 0; k < temp.size(); k++) {
        dicionario[esq + k] = temp[k];
    }
}

bool Cifra::buscaBinaria(const std::string& palavra) {
    int esq = 0, dir = dicionario.size() - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (dicionario[meio] == palavra) return true;
        if (dicionario[meio] < palavra) esq = meio + 1;
        else dir = meio - 1;
    }
    return false;
}

// --- LÓGICA DE CRIPTOGRAFIA ---

void Cifra::carregarEOrdenarDicionario(const std::string& caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    std::string palavra;
    if (!arquivo.is_open()) return;
    
    while (arquivo >> palavra) {
        dicionario.push_back(palavra);
    }
    arquivo.close();

    // Ordena o dicionário para permitir a Busca Binária
    if (!dicionario.empty()) {
        ordenarDicionario(0, dicionario.size() - 1);
    }
}

std::string Cifra::cifrar(const std::string& texto, int chave) {
    std::string resultado = "";
    for (char c : texto) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            resultado += (char)(((c - base + chave) % 26 + 26) % 26 + base);
        } else {
            resultado += c; // Mantém pontuações e espaços
        }
    }
    return resultado;
}

std::string Cifra::decifrar(const std::string& texto, int chave) {
    return cifrar(texto, -chave);
}

int Cifra::contarPalavrasValidas(const std::string& texto) {
    int contador = 0;
    std::string palavraAtual = "";
    
    for (char c : texto) {
        if (isalpha(c)) {
            palavraAtual += tolower(c);
        } else {
            if (!palavraAtual.empty()) {
                if (buscaBinaria(palavraAtual)) contador++;
                palavraAtual = "";
            }
        }
    }
    if (!palavraAtual.empty() && buscaBinaria(palavraAtual)) contador++;
    
    return contador;
}

void Cifra::quebrarCifra(const std::string& textoCifrado) {
    int melhorChave = 0;
    int maxPalavrasEncontradas = -1;
    std::string melhorTexto = "";

    // Tenta todas as 25 rotações possíveis do alfabeto
    for (int chave = 1; chave <= 25; chave++) {
        std::string textoTestado = decifrar(textoCifrado, chave);
        int palavrasValidas = contarPalavrasValidas(textoTestado);

        if (palavrasValidas > maxPalavrasEncontradas) {
            maxPalavrasEncontradas = palavrasValidas;
            melhorChave = chave;
            melhorTexto = textoTestado;
        }
    }

    std::cout << "[IA DE QUEBRA] Analise concluida." << std::endl;
    std::cout << "-> Chave de deslocamento descoberta: " << melhorChave << std::endl;
    std::cout << "-> Texto Original: " << melhorTexto << std::endl;
}