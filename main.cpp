#include <iostream>
#include <fstream>
#include <chrono>
#include "treesort.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    ofstream archivo("treesort_resultados.csv");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir resultados." << endl;
        return 1;
    }

    archivo << "Tamaño,Operaciones,Tiempo(ms)\n";

    for (int size = 10; size <= 1000; size += 10) {
        int operaciones = 0;
        double tiempoTotal = 0.0;

        // Ejecutar 5 veces y calcular el promedio.
        for (int i = 0; i < 5; i++) {
            Vector<int> datos = generarVectorAleatorio(size);
            auto inicio = high_resolution_clock::now();
            Vector<int> resultado = treesort(datos, operaciones);
            auto fin = high_resolution_clock::now();
            tiempoTotal += duration_cast<milliseconds>(fin - inicio).count();
        }

        // Guardar resultados promediados en el archivo.
        archivo << size << "," << operaciones / 5 << "," << tiempoTotal / 5 << "\n";
        cout << "Procesado tamaño: " << size << "\n";
    }

    archivo.close();
    cout << "Resultados guardados en treesort_resultados.csv\n";
    return 0;
}
