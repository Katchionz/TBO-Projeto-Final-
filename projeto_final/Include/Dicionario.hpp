#ifndef DICIONARIO_HPP
#define DICIONARIO_HPP

#include <string>

// Estrutura do Nó da Árvore de Prefixos (Trie)
struct TrieNode {
	bool fimDePalavra;
	TrieNode* filhos[26];

	TrieNode();
};

class Dicionario {
private:
	TrieNode* raiz;

	void liberarMemoria(TrieNode* node);
	std::string limparPalavra(const std::string& original);

public:
	Dicionario();
	~Dicionario();

	void inserir(const std::string& palavraBase);
	bool buscar(const std::string& palavraBase);
};

#endif // DICIONARIO_HPP
