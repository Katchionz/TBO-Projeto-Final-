#include "Dicionario.hpp"

#include <cctype>

using namespace std;

TrieNode::TrieNode() {
	fimDePalavra = false;
	for (int i = 0; i < 26; i++) filhos[i] = nullptr;
}

string Dicionario::limparPalavra(const string& original) {
	string limpa = "";
	for (size_t i = 0; i < original.length(); ++i) {
		unsigned char c = original[i];
		if (c < 128) {
			if (isalpha(c)) limpa += tolower(c);
		} else if (c == 0xC3 && i + 1 < original.length()) {
			i++;
			unsigned char next = original[i];
			if ((next >= 0xA0 && next <= 0xA5) || (next >= 0x80 && next <= 0x85)) limpa += 'a';
			else if (next == 0xA7 || next == 0x87) limpa += 'c';
			else if ((next >= 0xA8 && next <= 0xAB) || (next >= 0x88 && next <= 0x8B)) limpa += 'e';
			else if ((next >= 0xAC && next <= 0xAF) || (next >= 0x8C && next <= 0x8F)) limpa += 'i';
			else if ((next >= 0xB2 && next <= 0xB6) || (next >= 0x92 && next <= 0x96)) limpa += 'o';
			else if ((next >= 0xB9 && next <= 0xBC) || (next >= 0x99 && next <= 0x9C)) limpa += 'u';
		}
	}
	return limpa;
}

void Dicionario::liberarMemoria(TrieNode* node) {
	if (!node) return;
	for (int i = 0; i < 26; i++) liberarMemoria(node->filhos[i]);
	delete node;
}

Dicionario::Dicionario() {
	raiz = new TrieNode();
}

Dicionario::~Dicionario() {
	liberarMemoria(raiz);
}

void Dicionario::inserir(const string& palavraBase) {
	string palavra = limparPalavra(palavraBase);

	if (palavra.empty()){
        return;
    }

	TrieNode* atual = raiz;
	for (char c : palavra) {
		int indice = c - 'a';
		if (indice < 0 || indice >= 26){
            continue;
        }
		if (atual->filhos[indice] == nullptr) atual->filhos[indice] = new TrieNode();
		atual = atual->filhos[indice];
	}
	atual->fimDePalavra = true;
}

bool Dicionario::buscar(const string& palavraBase) {
	string palavra = limparPalavra(palavraBase);
	
    if (palavra.empty()) {
        return true;
    }

    TrieNode* atual = raiz;
	
    for (char c : palavra) {
		int indice = c - 'a';
		if (indice < 0 || indice >= 26){
            return false;
        } 

		if (atual->filhos[indice] == nullptr){ 
            return false;
        }

		atual = atual->filhos[indice];
	}
    
	return atual != nullptr && atual->fimDePalavra;
}
