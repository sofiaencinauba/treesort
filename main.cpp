#include "Treesort.hpp"
#include <iostream>
#include <chrono>
using namespace std::chrono;

int main(){
    Vector<int> vector;
    Treesort treesort;
    Vector <int> vector_ordenar = treesort.generar_vector_aleatorio(700);

    auto inicio = high_resolution_clock::now();
    // Algoritmo.
        treesort.ordenar_treesort(vector_ordenar);
    auto final = high_resolution_clock::now();
    auto duracion = duration_cast<milliseconds>(final - inicio);
    std::cout << "tiempo" << std::endl;
    std::cout << duracion.count(); // También se puede cargar a un archivo.
     std::cout << std::endl << "contador: " << treesort.operaciones() << std::endl;
    return 0;
}