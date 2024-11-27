#ifndef TREESORT_HPP
#define TREESORT_HPP

#include "Vector.hpp"
#include "Diccionario.hpp"

// Genera un vector aleatorio de tamaño `size` con valores entre 0 y 9999.
Vector<int> generarVectorAleatorio(int size);

// Implementación del algoritmo Treesort.
// Ordena los datos utilizando un ABB (Diccionario) y realiza un recorrido inorden.
// Devuelve un vector ordenado y actualiza la cantidad de operaciones realizadas.
Vector<int> treesort(Vector<int>& datos, int& operaciones);

#endif // TREESORT_HPP
