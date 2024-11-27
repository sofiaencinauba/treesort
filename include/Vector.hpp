#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <iostream>
class ExcepcionVector : public std::runtime_error {
    // Excepción específica y exclusiva para errores dentro del Vector.
    // Usar de la forma "throw ExcepcionVector(mensaje);"
    // cuando una precondición no se cumpla.
    // Ejemplo:
    //     if (condicion_de_error) {
    //         throw ExcepcionVector(mensaje);
    //     }
    // Pueden enviar por parámetro un mensaje descriptivo del error.
public:
    ExcepcionVector(std::string mensaje): runtime_error(mensaje) {
    }

    ExcepcionVector(): runtime_error("") {
    }
};

template<typename T>
class Vector {
private:

    //Constantes
    const size_t MAX_FISICO = 10;
    const size_t FACTOR_REDIMENSION = 2;

    //Atributos
    T* datos;
    size_t tamanio_logico;
    size_t tamanio_fisico;

    //Metodos
    /*
     * pre-condicion: Tipo debe ser 'A' (alta) o 'B' (baja)
     * post-condicion: El tamaño se ajusta según el factor de redimension (2)
     *              duplicando (si 'A') o dividiendo (si 'B'), manteniendo los datos
     */
    void redimensionar(char tipo);

public:
    // Constructor.
    Vector();
    /*
     * pre-condicion: El vector debe estar inicializado.
     * post-condicion: La informacion del vector se muestra sin modificar su contenido.
     */
    void mostrar();

    void mostrar_horizontal();

    Vector(size_t capacidad_inicial);

    // PRE: -
    // POST: Agrega el dato al final del vector.
    void alta(T dato);

    // PRE: El índice debe ser menor o igual que la cantidad de datos.
    // POST: Agrega el dato en el índice indicado,
    // moviendo todos los elementos siguientes.
    // Ejemplo:
    //      >> 1 3 2 7 0
    // alta(9, 2);
    //      >> 1 3 9 2 7 0
    void alta(T dato, size_t indice);

    // PRE: El vector no puede estar vacío.
    // POST: Elimina el último dato y lo devuelve.
    T baja();

    // PRE: El índice debe ser menor que la cantidad de datos.
    // POST: Elimina el dato en la posición indicada,
    // moviendo todos los elementos siguientes, y lo devuelve.
    // Ejemplo:
    //      >> 1 3 2 7 0
    // baja(1);
    //      >> 1 2 7 0
    T baja(size_t indice);

    /*
     * pre-condicion: El indice debe ser valido (estar dentro del rango del vector).
     * post-condicion: Devuelve el dato almacenado en la posicion indice sin modificar el vector.
     */
    T consultar(size_t indice);

    /*
    * pre-condicion: El indice debe ser valido (estar dentro del rango del vector).
    * post-condicion: El valor en la posicion indice es reemplazado por dato
    *               y el vector se actualiza con el nuevo valor.
    */
    T modificar(T dato, size_t indice);

    // PRE: -
    // POST: Devuelve true si el vector está vacío (es decir, si no hay datos).
    bool vacio();

    // PRE: -
    // POST: Devuelve la cantidad de datos del vector.
    size_t tamanio();

    // PRE: El índice debe ser menor que la cantidad de datos.
    // POST: Devuelve una referencia al dato indicado.
    T& operator[](size_t indice);

    // Constructor de copia (ya implementado).
    Vector(const Vector& vector);

    void invertir();

    // Operador de asignación (ya implementado).
    Vector& operator=(const Vector& vector);

    void ordenar_descendente(Vector<std::string>& vector_asociado);

    void ordenar_descendente(Vector<std::string>& asociado1,
                                    Vector<int>& asociado2,
                                    Vector<int>& asociado3,
                                    Vector<int>& asociado4);

    void inicializar(size_t tamanio_oficial, T valor_inicial);

    bool ya_esta(T dato);

    // Destructor.
    ~Vector();
};

//Constructor
template<typename T>
Vector<T>::Vector() {
    tamanio_logico = 0;
    tamanio_fisico = 0;
    datos = nullptr;
}

template<typename T>
bool Vector<T>::ya_esta(T dato){
    int contador = 0;
    for(size_t i = 0; i < tamanio_logico; i++){
        if(datos[i] == dato){
            contador++;
        }
    }
    return (contador > 0);
}

template<typename T>
Vector<T>::Vector(size_t capacidad_inicial) {
    if (capacidad_inicial == 0) {
        datos = nullptr;
        tamanio_logico = 0;
        tamanio_fisico = 0;
    } else {
        datos = new T[capacidad_inicial];
        tamanio_logico = capacidad_inicial;
        tamanio_fisico = capacidad_inicial;
    }
}


template<typename T>
void Vector<T>::redimensionar(char tipo) {
    T* datos_actualizados;

    //Redimensiona para agrandar el vector
    if(tipo == 'A') {
        //CASO 1: vector originalmente vacio
        if (datos == nullptr) {
            datos = new T[MAX_FISICO];
            tamanio_fisico = MAX_FISICO;
        }

        //CASO 2: vector esta al tope de su maximo fisico inicial
        else {
            size_t nuevo_maximo_fisico = tamanio_fisico * FACTOR_REDIMENSION;
            datos_actualizados = new T[nuevo_maximo_fisico];

            for(size_t i = 0; i < tamanio_logico; i++) {
                datos_actualizados[i] = datos[i];
            }

            delete[] datos;
            datos = datos_actualizados;
            tamanio_fisico = nuevo_maximo_fisico;
        }

    }

    // CASO B: Redimensiona para achicar el vector
    else {
        // Calcular el nuevo tamaño físico
        size_t nuevo_maximo_fisico = tamanio_logico * FACTOR_REDIMENSION;

        //aca debo crear un nuevo vector
        datos_actualizados = new T[nuevo_maximo_fisico];

        for (size_t i = 0; i < tamanio_logico; i++) {
            datos_actualizados[i] = datos[i];
        }

        delete[] datos;
        datos = datos_actualizados;
        tamanio_fisico = nuevo_maximo_fisico;
    }

}

template<typename T>
void Vector<T>::alta(T dato) {
    if(tamanio_fisico == tamanio_logico) {
        redimensionar('A');
    }
    datos[tamanio_logico] = dato;
    tamanio_logico++;
}

template<typename T>
void Vector<T>::alta(T dato, size_t indice) {
    if (indice > tamanio_logico) {
        throw ExcepcionVector("El indice es mayor a la cantidad de elementos");
    }
    if (tamanio_logico == tamanio_fisico) {
        redimensionar('A');
    }

    for (size_t i = tamanio_logico; i > indice; --i) {
        datos[i] = datos[i - 1];
    }

    datos[indice] = dato;

    tamanio_logico++;
}

template<typename T>
T Vector<T>::baja() {
    if(vacio()) {
        throw ExcepcionVector("No hay elementos para dar de baja");
    }

    T dato_eliminado = datos[tamanio_logico - 1];

    //CASO 1: el ultimo es el unico
    if(tamanio_logico == 1) {
        delete[] datos;
        datos = nullptr;
        tamanio_logico = 0;
        tamanio_fisico = 0;
    }

    //CASO 2: vector con + de un dato y elimino el ultimo
    else {
        tamanio_logico--;
        //le asigno el valor que tiene T por defecto a la última posición ahora no usada
        datos[tamanio_logico] = T();
    }

    //IMPORTANTE: comprobar si debo redimensionar para cumplir el factor 2
    if (tamanio_fisico > (tamanio_logico * FACTOR_REDIMENSION)) {
        redimensionar('B');
    }

    return dato_eliminado;
}

template<typename T>
T Vector<T>::baja(size_t indice) {
    if (vacio()) {
        throw ExcepcionVector("El vector esta vacio");
    }
    if (indice >= tamanio_logico) {
        throw ExcepcionVector("El indice esta fuera de rango");
    }


    T dato_eliminado = datos[indice];

    // Ordeno los elementos a la izquierda para evitar espacios "vacios"
    for (size_t i = indice; i < tamanio_logico - 1; ++i) {
        datos[i] = datos[i + 1];
    }

    tamanio_logico--;

    // Asigno el valor por defecto a la última posición ahora no usada
    datos[tamanio_logico] = T();

    //IMPORTANTE: comprobar si debo redimensionar para cumplir el factor 2
    if (tamanio_fisico > (tamanio_logico * FACTOR_REDIMENSION)) {
        redimensionar('B');
    }

    return dato_eliminado;
}

template<typename T>
T Vector<T>::consultar(size_t indice) {
    if (vacio()) {
        throw ExcepcionVector("El vector esta vacio");
    }
    if (indice >= tamanio_logico) {
        throw ExcepcionVector("El indice esta fuera de rango");
    }

    return datos[indice];
}


template<typename T>
T Vector<T>::modificar(T dato, size_t indice) {
    if (vacio()) {
        throw ExcepcionVector("El vector está vacío");
    }
    if (indice >= tamanio_logico) {
        throw ExcepcionVector("El índice está fuera de rango");
    }

    datos[indice] = dato;

    return datos[indice];
}
template<typename T>
bool Vector<T>::vacio() {
    return (tamanio_logico == 0);
}

template<typename T>
size_t Vector<T>::tamanio() {
    return tamanio_logico;
}

template<typename T>
T& Vector<T>::operator[](size_t indice) {
    if (indice >= tamanio_logico) {
        throw ExcepcionVector("El indice esta fuera de rango");
    }
    return datos[indice];
}


template<typename T>
Vector<T>::~Vector() {
    delete[] datos;
}

// Ya implementado. No hace falta modificarlo.
template<typename T>
Vector<T>::Vector(const Vector& vector) {
    datos = nullptr;
    tamanio_logico = vector.tamanio_logico;
    tamanio_fisico = vector.tamanio_fisico;
    if (tamanio_fisico) {
        datos = new T[tamanio_fisico];
        for (size_t i = 0; i < tamanio_logico; i++) {
            datos[i] = vector.datos[i];
        }
    }
}

// Ya implementado. No hace falta modificarlo.
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& vector) {
    if (this != &vector) {
        delete[] datos;
        datos = nullptr;
        tamanio_logico = vector.tamanio_logico;
        tamanio_fisico = vector.tamanio_fisico;
        if (tamanio_fisico) {
            datos = new T[tamanio_fisico];
            for (size_t i = 0; i < tamanio_logico; i++) {
                datos[i] = vector.datos[i];
            }
        }
    }
    return *this;
}

template<typename T>
void Vector<T>::mostrar() {
    for(size_t i = 0 ; i < tamanio_logico ; i++) {
        std::cout << "Indice: " << i + 1  << " | "<< datos[i] << std::endl;
    }
}

template<typename T>
void Vector<T>::mostrar_horizontal() {
    for(size_t i = 0 ; i < tamanio_logico ; i++) {
        std::cout << datos[i] << " | " ;
    }
    std::cout << std::endl;
}
template<typename T>
void Vector<T>::invertir() {
    if (vacio()) {
        throw ExcepcionVector("El vector está vacío, no se puede invertir.");
    }

    // Utilizamos el algoritmo de dos punteros
    size_t inicio = 0;
    size_t fin = tamanio_logico - 1;

    while (inicio < fin) {
        // Intercambiamos los elementos en las posiciones 'inicio' y 'fin'
        T temp = datos[inicio];
        datos[inicio] = datos[fin];
        datos[fin] = temp;

        // Movemos los punteros hacia el centro
        inicio++;
        fin--;
    }
}

template<typename T>
void Vector<T>::ordenar_descendente(Vector<std::string>& asociado) {
    if (vacio()) {
        throw ExcepcionVector("El vector principal está vacío, no se puede ordenar.");
    }

    if (tamanio_logico != asociado.tamanio()) {
        throw ExcepcionVector("El tamaño del vector asociado no coincide con el del vector principal.");
    }

    for (size_t i = 0; i < tamanio_logico - 1; ++i) {
        for (size_t j = 0; j < tamanio_logico - i - 1; ++j) {
            // Ordenamos el vector principal de mayor a menor
            if (datos[j] < datos[j + 1]) {
                // Intercambio en el vector principal
                T temp = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = temp;

                // Realizamos el mismo intercambio en el vector asociado
                std::string temp_asociado = asociado[j];
                asociado[j] = asociado[j + 1];
                asociado[j + 1] = temp_asociado;
            }
        }
    }
}

template<typename T>
void Vector<T>::ordenar_descendente(Vector<std::string>& asociado1,
                                    Vector<int>& asociado2,
                                    Vector<int>& asociado3,
                                    Vector<int>& asociado4) {
    if (vacio()) {
        throw ExcepcionVector("El vector principal está vacío, no se puede ordenar.");
    }

    // Validar que todos los vectores asociados tengan el mismo tamaño que el principal
    if (tamanio_logico != asociado1.tamanio() ||
        tamanio_logico != asociado2.tamanio() ||
        tamanio_logico != asociado3.tamanio() ||
        tamanio_logico != asociado4.tamanio()) {
        throw ExcepcionVector("El tamaño de uno o más vectores asociados no coincide con el del vector principal.");
    }

    // Ordenación tipo burbuja, extendida a los vectores asociados
    for (size_t i = 0; i < tamanio_logico - 1; ++i) {
        for (size_t j = 0; j < tamanio_logico - i - 1; ++j) {
            // Comparar para ordenar de mayor a menor
            if (datos[j] < datos[j + 1]) {
                // Intercambio en el vector principal
                T temp = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = temp;

                // Intercambio en el vector asociado1
                std::string temp_asociado1 = asociado1[j];
                asociado1[j] = asociado1[j + 1];
                asociado1[j + 1] = temp_asociado1;

                // Intercambio en el vector asociado2
                int temp_asociado2 = asociado2[j];
                asociado2[j] = asociado2[j + 1];
                asociado2[j + 1] = temp_asociado2;

                // Intercambio en el vector asociado3
                int temp_asociado3 = asociado3[j];
                asociado3[j] = asociado3[j + 1];
                asociado3[j + 1] = temp_asociado3;

                // Intercambio en el vector asociado4
                int temp_asociado4 = asociado4[j];
                asociado4[j] = asociado4[j + 1];
                asociado4[j + 1] = temp_asociado4;
            }
        }
    }
}

template<typename T>
void Vector<T>::inicializar(size_t tamanio_oficial, T valor_inicial) {
    if (tamanio_fisico < tamanio_oficial) {

        while (tamanio_fisico < tamanio_oficial) {
            redimensionar('A');
        }
    }

    for (size_t i = tamanio_logico; i < tamanio_oficial; ++i) {
        datos[i] = valor_inicial;
    }

    tamanio_logico = tamanio_oficial;
}

#endif
