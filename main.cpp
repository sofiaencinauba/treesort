#include "Treesort.hpp"

int main(){
    Treesort treesort;
    treesort.generar_vector_aleatorio(10);
    treesort.ordenar_treesort();
    std::cout << treesort.operaciones() << std::endl;
}