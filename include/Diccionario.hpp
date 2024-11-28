#ifndef DICCIONARIO_HPP
#define DICCIONARIO_HPP

#include <cstddef>
#include <stdexcept>
#include "NodoDiccionario.hpp"
#include "Vector.hpp"
// #include "Cola.hpp"

#include <stdio.h>

class ExcepcionDiccionario : public std::runtime_error {
public:
    ExcepcionDiccionario(std::string mensaje): runtime_error(mensaje) {
    }

    ExcepcionDiccionario(): runtime_error("") {
    }
};

// La clave debe implementar el operator<() y el operator==().
// Las claves menores a la clave de la raíz iran al subárbol izquierdo,
// mientras que las mayores iran al derecho.
template<typename Clave, typename T>
class Diccionario {
private:
    NodoDiccionario<Clave, T>* raiz;
    std::size_t cantidad_datos;

public:
    // Constructor.
    Diccionario();

    // Pre: La clave no puede existir en el diccionario.
    // Post: Agrega el dato asociado a la clave al diccionario. Si no hay datos, crea una nueva raíz.
    void alta(Clave clave, T dato, int& contador);
    //agrego
    void _alta_recursiva(Clave clave, T dato, NodoDiccionario<Clave, T>* nodo_comparacion, int& contador);

    //Pre: -
    //Post: devuelve el menor elemento del arbol con raiz nodo
    NodoDiccionario<Clave, T>* obtener_menor_elemento(NodoDiccionario<Clave, T>* nodo);

    // Pre: La clave debe existir en el diccionario.
    // Post: Elimina el dato asociado a la clave del diccionario y lo devuelve.
    // NOTA: El caso de baja con dos hijos se resuelve con sucesor inmediato. Se puede hacer swap del dato.
    T baja(Clave clave);
    T _baja_recursivo(Clave clave, NodoDiccionario<Clave, T>* nodo);

    //Pre: 
    //Post: busca en el ABB con raiz nodo la clave pasada por parametro y si existe en el diccionario devuelve el dato asociado a la clave,
    //sino lanza una excepcion. Se implementa de forma recursiva

    //devuelve true si el elemento ya esta, sino false
    bool buscar_elemento(Clave clave, NodoDiccionario<Clave, T>* nodo);

    bool buscar_elemento(Clave clave);

    // Pre: La clave debe existir en el diccionario.
    // Post: Devuelve una referencia al valor asociado a la clave.
    T& operator[](Clave clave);

    // Pre: -
    // Post: Devuelve el recorrido inorder.
    Vector<T> inorder();
    void _inorder_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& vector);


    // Pre: -
    // Post: Devuelve el recorrido preorder.
    Vector<T> preorder();
    void _preorder_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& vector);


    // Pre: -
    // Post: Devuelve el recorrido postorder.
    Vector<T> postorder();
    void _postorder_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& vector);

    // Pre: -
    // Post: Devuelve el recorrido en ancho (por niveles).
    Vector<T> ancho();

    // Pre: -
    // Post: Devuelve la cantidad de datos en el diccionario.
    std::size_t tamanio();

    // Pre: -
    // Post: Devuelve true si el diccionario está vacío.
    bool vacio();

    // El constructor de copia está deshabilitado.
    Diccionario(const Diccionario& diccionario) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Diccionario& diccionario) = delete;

    void mostrar_orden_descendiente();
    void _mostrar_orden_descendiente(NodoDiccionario<Clave, T>* nodo);

    Vector<Clave> obtener_claves();
    void obtener_claves_recursivo(NodoDiccionario<Clave, T>* nodo,Vector<Clave>& claves);

    Vector<T> obtener_valores();
    void obtener_valores_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& valores);

    // Destructor.
    ~Diccionario();
};

template<typename Clave, typename T>
Diccionario<Clave, T>::Diccionario() {
    cantidad_datos = 0;
    raiz = nullptr;
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::_alta_recursiva(Clave clave, T dato, NodoDiccionario<Clave, T>* nodo_comparacion, int& contador) {
    contador++;
    if(clave == nodo_comparacion->obtener_clave()){
        throw ExcepcionDiccionario("la clave ya existe en este diccionario");
    }
    if(clave < nodo_comparacion->obtener_clave()){
        if(!nodo_comparacion->obtener_hijo_izquierdo()){
            NodoDiccionario<Clave, T>* nodo_nuevo = new NodoDiccionario<Clave, T>(clave, dato);
            nodo_comparacion->cambiar_hijo_izquierdo(nodo_nuevo);
            nodo_nuevo->cambiar_padre(nodo_comparacion);
        }else{
            _alta_recursiva(clave, dato, nodo_comparacion->obtener_hijo_izquierdo(), contador);
        }
    }else{
        if(!nodo_comparacion->obtener_hijo_derecho()){
            NodoDiccionario<Clave, T>* nodo_nuevo = new NodoDiccionario<Clave, T>(clave, dato);
            nodo_comparacion->cambiar_hijo_derecho(nodo_nuevo);
            nodo_nuevo->cambiar_padre(nodo_comparacion);
        }else{
            _alta_recursiva(clave, dato, nodo_comparacion->obtener_hijo_derecho(), contador);
        }
    }
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::alta(Clave clave, T dato, int& contador) {
    if (cantidad_datos == 0){
        raiz = new NodoDiccionario<Clave, T>(clave, dato);
    }else{
        _alta_recursiva(clave, dato, raiz, contador);
    }
    cantidad_datos++;
}


template<typename Clave, typename T>
NodoDiccionario<Clave, T>* Diccionario<Clave, T>::obtener_menor_elemento(NodoDiccionario<Clave, T>* nodo) {
    //pre: nodo debe tener hijo derecho, y se debe llamar a la funcion con el hijo derecho
    if(nodo->obtener_hijo_izquierdo()){
        return obtener_menor_elemento(nodo->obtener_hijo_izquierdo());
    }
    return nodo;
}

template<typename Clave, typename T>
T Diccionario<Clave, T>::_baja_recursivo(Clave clave, NodoDiccionario<Clave, T>* nodo) {
    if (nodo->obtener_clave() == clave) {
        T dato = nodo->obtener_dato();
        // Caso nodo no tiene hijos
        if ((!nodo->obtener_hijo_izquierdo()) && (!nodo->obtener_hijo_derecho())) {
            if (nodo == raiz) {
                raiz = nullptr;
            } else {
                if (nodo->obtener_padre()->obtener_clave() > clave) {
                    nodo->obtener_padre()->cambiar_hijo_izquierdo(nullptr);
                } else {
                    nodo->obtener_padre()->cambiar_hijo_derecho(nullptr);
                }
            }
        // Caso nodo tiene un solo hijo (el izquierdo)
        } else if (nodo->obtener_hijo_izquierdo() && !nodo->obtener_hijo_derecho()) {
            if (nodo == raiz) {
                raiz = nodo->obtener_hijo_izquierdo();
                nodo->obtener_hijo_izquierdo()->cambiar_padre(nullptr);
            } else {
                if ((nodo->obtener_padre())->obtener_clave() > clave) {
                    (nodo->obtener_padre())->cambiar_hijo_izquierdo(nodo->obtener_hijo_izquierdo());
                } else {
                    (nodo->obtener_padre())->cambiar_hijo_derecho(nodo->obtener_hijo_izquierdo());
                }
                nodo->obtener_hijo_izquierdo()->cambiar_padre(nodo->obtener_padre());
            }
        // Caso nodo tiene un solo hijo (el derecho)
        } else if (nodo->obtener_hijo_derecho() && !nodo->obtener_hijo_izquierdo()) {
            if (nodo == raiz) {
                raiz = nodo->obtener_hijo_derecho();
                nodo->obtener_hijo_derecho()->cambiar_padre(nullptr);
            } else {
                if ((nodo->obtener_padre())->obtener_clave() > clave) {
                    (nodo->obtener_padre())->cambiar_hijo_izquierdo(nodo->obtener_hijo_derecho());
                } else {
                    (nodo->obtener_padre())->cambiar_hijo_derecho(nodo->obtener_hijo_derecho());
                }
                nodo->obtener_hijo_derecho()->cambiar_padre(nodo->obtener_padre());
            }
        // Caso nodo tiene dos hijos
        } else {
            NodoDiccionario<Clave, T>* inmediato_sucesor = obtener_menor_elemento(nodo->obtener_hijo_derecho());
            T dato_sucesor = inmediato_sucesor->obtener_dato();
            Clave clave_sucesor = inmediato_sucesor->obtener_clave();
            inmediato_sucesor->cambiar_dato(nodo->obtener_dato());
            inmediato_sucesor->cambiar_clave(clave);
            nodo->cambiar_dato(dato_sucesor);
            nodo->cambiar_clave(clave_sucesor);
            if (inmediato_sucesor->obtener_hijo_derecho()) {
                if (inmediato_sucesor->obtener_padre()->obtener_clave() > clave_sucesor) {
                    inmediato_sucesor->obtener_padre()->cambiar_hijo_izquierdo(inmediato_sucesor->obtener_hijo_derecho());
                } else {
                    inmediato_sucesor->obtener_padre()->cambiar_hijo_derecho(inmediato_sucesor->obtener_hijo_derecho());
                }
                inmediato_sucesor->obtener_hijo_derecho()->cambiar_padre(inmediato_sucesor->obtener_padre());
                inmediato_sucesor->cambiar_hijo_derecho(nullptr);
            } else {
                if (inmediato_sucesor->obtener_padre()->obtener_clave() > clave_sucesor) {
                    inmediato_sucesor->obtener_padre()->cambiar_hijo_izquierdo(nullptr);
                } else {
                    inmediato_sucesor->obtener_padre()->cambiar_hijo_derecho(nullptr);
                }
            }
            inmediato_sucesor->cambiar_padre(nullptr);
            delete inmediato_sucesor;
            cantidad_datos--;
            return dato;
        }
        nodo->cambiar_padre(nullptr);
        nodo->cambiar_hijo_derecho(nullptr);
        nodo->cambiar_hijo_izquierdo(nullptr);
        delete nodo;
        cantidad_datos--;
        return dato;
    } else {
        // Caso rama izquierda
        if (nodo->obtener_clave() > clave) {
            if (!nodo->obtener_hijo_izquierdo()) {
                throw ExcepcionDiccionario("la clave no existe en el diccionario");
            }
            return _baja_recursivo(clave, nodo->obtener_hijo_izquierdo());
        }
        // Caso rama derecha
        if (nodo->obtener_clave() < clave) {
            if (!nodo->obtener_hijo_derecho()) {
                throw ExcepcionDiccionario("la clave no existe en el diccionario");
            }
            return _baja_recursivo(clave, nodo->obtener_hijo_derecho());
        }
    }

    // Agregar un retorno por defecto (nunca debería alcanzarse si la lógica es correcta)
    throw ExcepcionDiccionario("Error inesperado en _baja_recursivo.");
}



template<typename Clave, typename T>
T Diccionario<Clave, T>::baja(Clave clave) {
    if (cantidad_datos == 0){
        throw ExcepcionDiccionario("el diccionario esta vacio");
    }else{
        return _baja_recursivo(clave, raiz);
    }
}

template<typename Clave, typename T>
bool Diccionario<Clave, T>::buscar_elemento(Clave clave, NodoDiccionario<Clave, T>* nodo) {
    if(clave == nodo->obtener_clave()){
        return true;
    }else if(clave < nodo->obtener_clave()){
        if(nodo->obtener_hijo_izquierdo()){
            return buscar_elemento(clave, nodo->obtener_hijo_izquierdo());
        }
    }else{
        if(nodo->obtener_hijo_derecho()){
            return buscar_elemento(clave, nodo->obtener_hijo_derecho());
        }
    }
    // throw ExcepcionDiccionario("la clave no esta en el diccionario");
    return false;
}

template<typename Clave, typename T>
bool Diccionario<Clave, T>::buscar_elemento(Clave clave) {
    if (raiz == nullptr) {
        return false;
    }
    return buscar_elemento(clave, raiz);
}


template<typename Clave, typename T>
T& Diccionario<Clave, T>::operator[](Clave clave) {
    if(raiz){
        return buscar_elemento(clave, raiz);
    }
    throw ExcepcionDiccionario("no hay elementos");
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::_inorder_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& recorrido) {
    //IRD
    if(nodo->obtener_hijo_izquierdo()){
        _inorder_recursivo(nodo->obtener_hijo_izquierdo(), recorrido);
    }
    recorrido.alta(nodo->obtener_dato());
    if(nodo->obtener_hijo_derecho()){
        _inorder_recursivo(nodo->obtener_hijo_derecho(), recorrido);
    }

}

template<typename Clave, typename T>
Vector<T> Diccionario<Clave, T>::inorder() {
    Vector<T> recorrido;
    if(raiz){
        _inorder_recursivo(raiz, recorrido);
    }
    return recorrido;
}



template<typename Clave, typename T>
void Diccionario<Clave, T>::_preorder_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& recorrido) {
    recorrido.alta(nodo->obtener_dato());
    if(nodo->obtener_hijo_izquierdo()){
        _preorder_recursivo(nodo->obtener_hijo_izquierdo(), recorrido);
    }
    if(nodo->obtener_hijo_derecho()){
        _preorder_recursivo(nodo->obtener_hijo_derecho(), recorrido);
    }
}

template<typename Clave, typename T>
Vector<T> Diccionario<Clave, T>::preorder() {
    //RID
    Vector<T> recorrido;
    if(cantidad_datos != 0){
        _preorder_recursivo(raiz, recorrido);
    }
    return recorrido;
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::_postorder_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& recorrido) {
    //IDR

    if(nodo->obtener_hijo_izquierdo()){
        _postorder_recursivo(nodo->obtener_hijo_izquierdo(), recorrido);
    }
    if(nodo->obtener_hijo_derecho()){
        _postorder_recursivo(nodo->obtener_hijo_derecho(), recorrido);
    }
    recorrido.alta(nodo->obtener_dato());
}

template<typename Clave, typename T>
Vector<T> Diccionario<Clave, T>::postorder() {
    //RID
    Vector<T> recorrido;
    if(cantidad_datos != 0){
        _postorder_recursivo(raiz, recorrido);
    }
    return recorrido;
}

// template<typename Clave, typename T>
// Vector<T> Diccionario<Clave, T>::ancho() {
//     Vector<T> recorrido;
//     Cola<NodoDiccionario<Clave, T>*> cola_nodos;
//     if(raiz){
//         cola_nodos.alta(raiz);
//     }
//     while(!cola_nodos.vacio()){
//         NodoDiccionario<Clave, T>* nodo_actual = cola_nodos.primero();
//         cola_nodos.baja();

//         if(nodo_actual->obtener_hijo_izquierdo()){
//             cola_nodos.alta(nodo_actual->obtener_hijo_izquierdo());
//         }
//         if(nodo_actual->obtener_hijo_derecho()){
//             cola_nodos.alta(nodo_actual->obtener_hijo_derecho());
//         }
//         recorrido.alta(nodo_actual->obtener_dato());
//     }
//     return recorrido;
// }

template<typename Clave, typename T>
std::size_t Diccionario<Clave, T>::tamanio() {
    return cantidad_datos;
}

template<typename Clave, typename T>
bool Diccionario<Clave, T>::vacio() {
    return cantidad_datos == 0;
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::_mostrar_orden_descendiente(NodoDiccionario<Clave, T>* nodo) {
    //DRI
    if(nodo->obtener_hijo_derecho()){
        _mostrar_orden_descendiente(nodo->obtener_hijo_derecho());
    }
    std::cout << "clave: " << nodo->obtener_clave() << std::endl;
    std::cout << "dato: " << nodo->obtener_dato() << std::endl;
    if(nodo->obtener_hijo_izquierdo()){
        _mostrar_orden_descendiente(nodo->obtener_hijo_izquierdo());
    }
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::mostrar_orden_descendiente() {
    if(raiz){
        _mostrar_orden_descendiente(raiz);
    }

}

template<typename Clave, typename T>
Diccionario<Clave, T>::~Diccionario() {
    delete raiz;
}

template<typename Clave, typename T>
Vector<Clave> Diccionario<Clave,T>::obtener_claves() {
    Vector<Clave> claves;
    if(raiz){
        obtener_claves_recursivo(raiz,claves);
    }
    return claves;
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::obtener_claves_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<Clave>& claves) {
    if (nodo == nullptr) { // Verificar si el nodo es nulo
        return;
    }
    // Recorrer el hijo izquierdo
    if (nodo->obtener_hijo_izquierdo()) {
        obtener_claves_recursivo(nodo->obtener_hijo_izquierdo(), claves);
    }

    // Procesar el nodo actual
    claves.alta(nodo->obtener_clave());

    // Recorrer el hijo derecho
    if (nodo->obtener_hijo_derecho()) {
        obtener_claves_recursivo(nodo->obtener_hijo_derecho(), claves);
    }
}

template<typename Clave, typename T>
Vector<T> Diccionario<Clave,T>::obtener_valores() {
    Vector<T> valores;
    if(raiz){
        obtener_valores_recursivo(raiz,valores);
    }
    return valores;
}

template<typename Clave, typename T>
void Diccionario<Clave, T>::obtener_valores_recursivo(NodoDiccionario<Clave, T>* nodo, Vector<T>& valores) {
    if (nodo == nullptr) { // Verificar si el nodo es nulo
        return;
    }
    // Recorrer el hijo izquierdo
    if (nodo->obtener_hijo_izquierdo()) {
        obtener_valores_recursivo(nodo->obtener_hijo_izquierdo(), valores);
    }

    // Procesar el nodo actual
    valores.alta(nodo->obtener_dato());

    // Recorrer el hijo derecho
    if (nodo->obtener_hijo_derecho()) {
        obtener_valores_recursivo(nodo->obtener_hijo_derecho(), valores);
    }
}







#endif