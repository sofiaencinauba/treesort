#ifndef TREESORT_HPP
#define TREESORT_HPP

#include <fstream>
#include <cstdlib>
#include <chrono>
#include "Diccionario.hpp"
#include "Vector.hpp"

class Treesort{
    private:
        int cantidad_operaciones;
    public:
        Treesort();
        Treesort(Vector<int>);
        Vector<int> generar_vector_aleatorio(int tamanio);
        void ordenar_treesort(Vector<int> vector);
        int operaciones();
};

Treesort::Treesort(){

}

void Treesort::ordenar_treesort(Vector<int> vector){
    Diccionario<int, int> diccionario;
    cantidad_operaciones = 0;
    //creo el diccionario y lo ordeno en esta funcion asi mide bien el tiempo
    for(size_t i = 0; i < vector.tamanio(); i++){
        diccionario.alta(vector[i], vector[i], cantidad_operaciones);
    }
    Vector<int> vector_ordenado = diccionario.inorder();
}

Vector<int> Treesort::generar_vector_aleatorio(int tamanio){
    Vector<int> vector;
    int i = 0;
    while(i < tamanio){
        int numero_alta = rand() % 10000;
        if(vector.ya_esta(numero_alta)){
        }else{
            vector.alta(numero_alta);
            i++;
        }
    }
    return vector;
}



int Treesort::operaciones(){
    return cantidad_operaciones;
}

#endif