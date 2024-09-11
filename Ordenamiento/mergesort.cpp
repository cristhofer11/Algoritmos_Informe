#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

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

    // Leer el archivo y cargar los números en el vector
    while (archivo >> numero) {
        dataset.push_back(numero);
    }
    
    archivo.close();
    return dataset;
}

/**
 * @brief Realiza la mezcla (merge) de dos subarreglos ordenados.
 * 
 * @param arreglo Vector que contiene los elementos a ordenar.
 * @param inicio Índice inicial del primer subarreglo.
 * @param medio Índice que divide el primer y segundo subarreglo.
 * @param fin Índice final del segundo subarreglo.
 */
void merge(vector<int>& arreglo, int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    // Crear subarreglos temporales
    vector<int> izquierda(n1), derecha(n2);

    // Copiar datos a los subarreglos temporales
    for (int i = 0; i < n1; i++) {
        izquierda[i] = arreglo[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        derecha[j] = arreglo[medio + 1 + j];
    }

    // Mezclar los subarreglos
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (izquierda[i] <= derecha[j]) {
            arreglo[k++] = izquierda[i++];
        } else {
            arreglo[k++] = derecha[j++];
        }
    }

    // Copiar los elementos restantes de la izquierda (si quedan)
    while (i < n1) {
        arreglo[k++] = izquierda[i++];
    }

    // Copiar los elementos restantes de la derecha (si quedan)
    while (j < n2) {
        arreglo[k++] = derecha[j++];
    }
}

/**
 * @brief Implementa el algoritmo de Merge Sort para ordenar un arreglo.
 * 
 * @param arreglo Vector a ordenar.
 * @param inicio Índice inicial del subarreglo.
 * @param fin Índice final del subarreglo.
 */
void mergeSort(vector<int>& arreglo, int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        // Ordenar las dos mitades
        mergeSort(arreglo, inicio, medio);
        mergeSort(arreglo, medio + 1, fin);

        // Mezclar las mitades ordenadas
        merge(arreglo, inicio, medio, fin);
    }
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
 * @brief Mide el tiempo de ejecución del algoritmo Merge Sort y muestra el resultado.
 * 
 * @param nombreArchivo Nombre del archivo del dataset.
 * @param datos Vector que contiene el dataset a ordenar.
 */
void medirTiempo(const string& nombreArchivo, vector<int>& datos) {
    string descripcionDataset = obtenerDescripcionDataset(nombreArchivo);

    // Medir el tiempo de ejecución del algoritmo de ordenamiento
    auto inicio = chrono::high_resolution_clock::now();
    mergeSort(datos, 0, datos.size() - 1);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    // Mostrar el tiempo de ejecución
    cout << "Merge Sort de " << descripcionDataset << " - Tiempo: " << duracion.count() << " ms" << endl;
}

/**
 * @brief Función principal que lee datasets desde archivos y mide el tiempo de ordenamiento usando Merge Sort.
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
