#ifndef KMP_HPP
#define KMP_HPP

#include <string>
#include <vector>

// Assinaturas dos métodos originais do seu projeto
std::vector<int> calculaLPS_Original(const std::string& padrao);
void buscaKMP_Original(const std::string& texto, const std::string& palavra);

#endif // KMP_HPP