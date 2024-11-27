#ifndef TREESORT_HPP
#define TREESORT_HPP

#include <fstream>
#include <cstdlib>
#include <chrono>
#include "Diccionario.hpp"
#include "Vector.hpp"

class Treesort{
    private:
        Vector<int> vector;
        Diccionario<int, int> diccionario;
        int cantidad_operaciones;
    public:
        Treesort();
        void generar_vector_aleatorio(int tamanio);
        void ordenar_treesort();
        int operaciones();
};

void Treesort::generar_vector_aleatorio(int tamanio){
    //para poder crear varios vectores consecutivamente
    while(!vector.vacio()){
        vector.baja();
    }
    for(int i = 0; i < tamanio; i++){
        int numero_alta = rand() % 10000;
        if(vector.ya_esta(numero_alta)){
            i--;
            continue;
        }else{
            vector.alta(numero_alta);
        }
    }
    std::cout << "vector antes" << std::endl;
    vector.mostrar();
}

Treesort::Treesort(){
    cantidad_operaciones = 0;
}

void Treesort::ordenar_treesort(){
    //creo el diccionario y lo ordeno en esta funcion asi mide bien el tiempo
    for(size_t i = 0; i < vector.tamanio(); i++){
        diccionario.alta(vector[i], vector[i], cantidad_operaciones);
    }
    Vector<int> vector_ordenado = diccionario.inorder(cantidad_operaciones);
    std::cout << "vector despues" << std::endl;
    vector_ordenado.mostrar();
}

int Treesort::operaciones(){
    return cantidad_operaciones;
}

#endif