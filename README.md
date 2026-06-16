 TBO - Projeto Final de Algoritmos de Busca e Ordenação em Texto


## 📁 Estrutura do Projeto

O projeto adota o padrão de organização da indústria de software, separando responsabilidades de forma clara e isolando dados, contratos e implementações:


TBO-Projeto-Final/

├── 📁 Base de dados/             # Arquivos de dados (.txt) para alimentação das estruturas

│   ├── dicionario.txt            # Dicionário bruto original (KMP)

│   ├── words.txt                 # Dicionário purificado e padronizado (Trie/Levenshtein/Cifra)

│   ├── texto_teste_correto.txt   # Massa de teste sem infrações ortográficas

│   ├── texto_teste_com_erro.txt  # Massa de teste com erros ortográficos forçados

│   └── texto_teste_3.txt         # Texto longo para benchmark de volumetria

├── 📁 include/                   # Cabeçalhos e definições de contratos (.hpp)
│   ├── Buscador.hpp              # Definições do Aho-Corasick e assinaturas de benchmarks
│   ├── Cifra.hpp                 # Assinaturas de criptografia, MergeSort e Busca Binária
│   ├── Corretor.hpp              # Definições da matriz de Distância de Levenshtein
│   ├── Dicionario.hpp            # Estrutura de nós e árvore Trie para correção
│   ├── KMP.hpp                   # Módulo isolado do KMP Original
│   └── MenuMetodos.hpp           # Encapsulamento das rotinas do menu do sistema
│
└── 📁 src/                       # Códigos-fonte com as regras de negócio (.cpp)
    ├── Buscador.cpp              # Construção do autômato de Aho-Corasick (BFS manual)
    ├── Cifra.cpp                 # MergeSort, Cifra de César e IA de ataque de força bruta
    ├── Corretor.cpp              # Algoritmo de Programação Dinâmica de Levenshtein
    ├── Dicionario.cpp            # Lógica de inserção/busca em Trie e parser UTF-8
    ├── KMP.cpp                   # Lógica matemática e processamento do array LPS
    ├── MenuMetodos.cpp           # Orquestrador de leitura de arquivos e chamadas de classes
    └── Main.cpp                  # Ponto de entrada limpo e Controlador (Switch/Case)

Desafios Concluídos e Funcionalidades

### 1. Busca Exata com KMP Original (Módulo KMP)

* Reincorporação do algoritmo Knuth-Morris-Pratt original do projeto. Utiliza o vetor **LPS (Longest Pattern Prefix which is also Suffix)** para pular comparações redundantes e encontrar padrões exatos de texto de forma linear em tempo $O(N + M)$.

### 2. Verificação Ortográfica Avançada (Módulo Dicionário)

* Carregamento de wordlists extensas em uma **Árvore de Prefixos (Trie) customizada**. A busca de conformidade lexical de cada token ocorre em complexidade constante $O(L)$, sendo $L$ o comprimento da palavra avaliada, independentemente do tamanho do dicionário.

### 3. Sugestão de Correção Ortográfica (Módulo Corretor)

* Implementação da **Distância de Levenshtein** por meio de Programação Dinâmica bidimensional. Quando a Trie detecta uma palavra inválida, a matriz calcula os custos mínimos de inserção, deleção e substituição de caracteres. Um algoritmo de ordenação linear mantém em tempo real as 3 melhores sugestões sem custos adicionais de ordenação sobre toda a base de dados.

### 4. Criptografia e Quebra de Cifra Sem Chave (Módulo Cifra)

* Implementação de um módulo criptográfico baseado na Cifra de César. A **quebra automática** avalia todas as 25 rotações possíveis do alfabeto. Para cada rotação, o texto resultante é quebrado em tokens e validado via **Busca Binária ($O(\log N)$)** contra o dicionário. Para permitir a Busca Binária, o dicionário é ordenado na inicialização por meio de uma rotina nativa de **MergeSort** implementada do zero.

### 5. Busca Paralela de Múltiplos Padrões (Módulo Buscador)

* Desenvolvimento do sofisticado algoritmo de **Aho-Corasick**. O sistema constrói um autômato de estados ligando os nós da Trie a links de falha (*fail links*) calculados através de uma busca em largura (**BFS iterativa com fila alocada manualmente**). Isso permite que centenas de palavras-chave sejam rastreadas em paralelo realizando **apenas uma única varredura linear** sobre o arquivo de texto.

Decisões de Projeto e Critérios de Qualidade

1. **Zero STL Pronta para Algoritmos Core:** Nenhuma chamada a `std::sort`, `std::find`, ou estruturas complexas prontas como `std::unordered_set` ou `std::queue` foi efetuada. Filas para o BFS, partições do MergeSort e encadeamentos da Trie foram gerenciados nativamente por ponteiros e vetores base.
2. **Arquitetura Desacoplada (Padrão Controller):** O arquivo `Main.cpp` não possui regras de leitura de arquivos ou computação matemática. Ele delega o controle para o módulo `MenuMetodos`, mantendo o código extensível e limpo.
3. **Gerenciamento de Memória Preciso:** Todos os nós dinâmicos criados pela Trie do Dicionário e pelo Autômato de Aho-Corasick são varridos e desalocados recursivamente em seus respectivos destrutores (`~Dicionario` e `~Buscador`), prevenindo *Memory Leaks*.
4. **Sanitização de Strings e Parser UTF-8:** Integração de uma rotina no pré-processamento de strings capaz de interceptar os bytes especiais de acentuação do português (`0xC3`) em formato UTF-8, convertendo caracteres complexos (como `á`, `ç`, `õ`) para ASCII minúsculo equivalente e expurgando pontuações das bordas.

