#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm> // Para std::sort

using namespace std;

/**
 * @brief Lee un dataset desde un archivo de texto y lo carga en un vector de enteros.
 * 
 * @param nombreArchivo Nombre del archivo que contiene los datos.
 * @return vector<int> Vector que contiene el dataset leído.
 */
vector<int> leerDatasetDesdeArchivo(const string& nombreArchivo) {
    vector<int> dataset;
    ifstream archivo(nombreArchivo);
    int numero;

    // Leer los datos desde el archivo y almacenarlos en el vector
    while (archivo >> numero) {
        dataset.push_back(numero);
    }
    
    archivo.close();
    return dataset;
}

/**
 * @brief Extrae la descripción del tipo de dataset y su tamaño a partir del nombre del archivo.
 * 
 * @param nombreArchivo Nombre del archivo que contiene el dataset.
 * @return string Descripción del dataset.
 */
string obtenerDescripcionDataset(const string& nombreArchivo) {
    string descripcion;

    // Determinar el tipo de dataset
    if (nombreArchivo.find("aleatorio") != string::npos) {
        descripcion = "dataset aleatorio";
    } else if (nombreArchivo.find("parcialmente_ordenado") != string::npos) {
        descripcion = "dataset parcialmente ordenado";
    } else if (nombreArchivo.find("ordenado") != string::npos) {
        descripcion = "dataset ordenado";
    }

    // Determinar el tamaño del dataset según el nombre del archivo
    if (nombreArchivo.find("100000") != string::npos) {
        descripcion += " de 100000 elementos";
    } else if (nombreArchivo.find("10000") != string::npos) {
        descripcion += " de 10000 elementos";
    } else if (nombreArchivo.find("1000") != string::npos) {
        descripcion += " de 1000 elementos";
    }

    return descripcion;
}

/**
 * @brief Mide el tiempo de ejecución de la función std::sort y muestra el resultado.
 * 
 * @param nombreArchivo Nombre del archivo del dataset.
 * @param datos Vector que contiene el dataset a ordenar.
 */
void medirTiempo(const string& nombreArchivo, vector<int>& datos) {
    string descripcionDataset = obtenerDescripcionDataset(nombreArchivo);

    // Medir el tiempo de ejecución del algoritmo de ordenamiento
    auto inicio = chrono::high_resolution_clock::now();
    sort(datos.begin(), datos.end());
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    // Mostrar el tiempo de ejecución
    cout << "Biblioteca estándar (std::sort) de " << descripcionDataset << " - Tiempo: " << duracion.count() << " ms" << endl;
}

/**
 * @brief Función principal que lee datasets desde archivos y mide el tiempo de ordenamiento usando std::sort.
 * 
 * @return int Código de estado de la ejecución.
 */
int main() {
    // Archivos de datasets a leer
    string archivos[] = {
        "dataset_aleatorio_1000.txt", "dataset_parcialmente_ordenado_1000.txt", "dataset_ordenado_1000.txt",
        "dataset_aleatorio_10000.txt", "dataset_parcialmente_ordenado_10000.txt", "dataset_ordenado_10000.txt",
        "dataset_aleatorio_100000.txt", "dataset_parcialmente_ordenado_100000.txt", "dataset_ordenado_100000.txt"
    };

    // Leer cada dataset y medir el tiempo de ordenamiento
    for (const string& archivo : archivos) {
        vector<int> datos = leerDatasetDesdeArchivo(archivo);
        medirTiempo(archivo, datos);
    }

    return 0;
}
