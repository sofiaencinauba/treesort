#include "Treesort.hpp"
#include <iostream>
#include <chrono>
using namespace std::chrono;

int main(){
    Treesort treesort;
    treesort.generar_vector_aleatorio(10);
    treesort.ordenar_treesort();
    std::cout << treesort.operaciones() << std::endl;

    treesort.generar_vector_aleatorio(10);
    auto inicio = high_resolution_clock::now();
    // Algoritmo.
    treesort.ordenar_treesort();
    auto final = high_resolution_clock::now();
    auto duracion = duration_cast<milliseconds>(final - inicio);
    std::cout << "tiempo" << std::endl;
    std::cout << duracion.count(); // También se puede cargar a un archivo.
    return 0;
}