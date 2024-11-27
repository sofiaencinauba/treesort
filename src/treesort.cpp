#include "treesort.hpp"
#include <cstdlib>

// Genera un vector aleatorio de tamaño `size` con valores entre 0 y 9999.
Vector<int> generarVectorAleatorio(int size) {
    Vector<int> vector;
    for (int i = 0; i < size; i++) {
        vector.alta(rand() % 10000);
    }
    return vector;
}

// Implementación del algoritmo Treesort.
// Utiliza un ABB (Diccionario) para ordenar los datos y realiza un recorrido inorden.
Vector<int> treesort(Vector<int>& datos, int& operaciones) {
    Diccionario<int, int> diccionario;
    Vector<int> ordenado;

    // Insertar los datos en el ABB y contar operaciones.
    for (size_t i = 0; i < datos.tamanio(); i++) {
        if (!diccionario.existe(datos[i])) { // Verifica si la clave no existe antes de insertarla.
        diccionario.alta(datos[i], datos[i]); // Clave y valor iguales.
        operaciones++;
    }
}


    // Realizar recorrido inorden para obtener el vector ordenado.
    ordenado = diccionario.inorder();
    return ordenado;
}
