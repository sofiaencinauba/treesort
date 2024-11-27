#ifndef COLA_HPP
#define COLA_HPP

#include <cstddef>
#include <stdexcept>
#include "NodoLista.hpp"

class ExcepcionCola : public std::runtime_error {
public:
    ExcepcionCola(std::string mensaje): runtime_error(mensaje) {
    }

    ExcepcionCola(): runtime_error("") {
    }
};

template<typename T>
class Cola {
private:
    NodoLista<T>* primer_nodo;
    NodoLista<T>* ultimo_nodo;
    size_t cantidad_datos;

public:
    // Constructor.
    Cola();

    // Pre: -
    // Post: Agrega el dato al final de la cola.
    void alta(T dato);

    // Pre: La cola no puede estar vacía.
    // Post: Elimina y devuelve el primer dato de la cola.
    T baja();

    // Pre: La cola no puede estar vacía.
    // Post: Devuelve el primer dato de la cola.
    T primero();

    // Pre: -
    // Post: Devuelve la cantidad de datos de la cola.
    size_t tamanio();

    // Pre: -
    // Post: Devuelve true si la cola esta vacía.
    bool vacio();

    // El constructor de copia está deshabilitado.
    Cola(const Cola& cola) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Cola& cola) = delete;

    // Destructor.
    ~Cola();
};

template<typename T>
Cola<T>::Cola() : primer_nodo(nullptr), ultimo_nodo(nullptr), cantidad_datos(0) {
}

template<typename T>
void Cola<T>::alta(T dato) {
    NodoLista<T>* nuevo_nodo = new NodoLista<T>(dato);
    if (vacio()) {
        primer_nodo = nuevo_nodo;
    } else {
        ultimo_nodo->cambiar_siguiente(nuevo_nodo);
    }
    ultimo_nodo = nuevo_nodo;
    cantidad_datos++;
}


template<typename T>
T Cola<T>::baja() {
    if (vacio()) {
        throw ExcepcionCola("La cola esta vacia.");
    }
    NodoLista<T>* nodo_a_eliminar = primer_nodo;
    T dato = nodo_a_eliminar->obtener_dato();
    primer_nodo = primer_nodo->obtener_siguiente();
    if (vacio()) {
        ultimo_nodo = nullptr;
    }
    delete nodo_a_eliminar;
    cantidad_datos--;
    return dato;
}


template<typename T>
T Cola<T>::primero() {
    if (vacio()) {
        throw ExcepcionCola("La cola esta vacia.");
    }
    return primer_nodo->obtener_dato();
}


template<typename T>
size_t Cola<T>::tamanio() {
    return cantidad_datos;
}

template<typename T>
bool Cola<T>::vacio() {
    return cantidad_datos == 0;
}

template<typename T>
Cola<T>::~Cola() {
    while (!vacio()) {
        baja();
    }
}

#endif