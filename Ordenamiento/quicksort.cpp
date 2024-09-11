#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstdlib>  // Para usar rand()

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
 * @brief Realiza la partición del arreglo utilizando un pivote aleatorio para el algoritmo Quick Sort.
 * 
 * @param arreglo Vector a ordenar.
 * @param bajo Índice inicial del subarreglo.
 * @param alto Índice final del subarreglo.
 * @return int Índice del pivote.
 */
int particion(vector<int>& arreglo, int bajo, int alto) {
    // Elegir un pivote aleatorio para evitar el peor caso en listas ordenadas
    int pivoteIndex = bajo + rand() % (alto - bajo + 1);
    swap(arreglo[pivoteIndex], arreglo[alto]);  // Mover el pivote al final

    int pivote = arreglo[alto];  // El pivote es ahora el último elemento
    int i = bajo - 1;

    // Colocar todos los elementos menores que el pivote a la izquierda y los mayores a la derecha
    for (int j = bajo; j <= alto - 1; j++) {
        if (arreglo[j] < pivote) {
            i++;
            swap(arreglo[i], arreglo[j]);
        }
    }
    swap(arreglo[i + 1], arreglo[alto]);  // Colocar el pivote en su posición correcta
    return i + 1;  // Retornar el índice del pivote
}

/**
 * @brief Implementa el algoritmo de Quick Sort utilizando un pivote aleatorio.
 * 
 * @param arreglo Vector a ordenar.
 * @param bajo Índice inicial del subarreglo.
 * @param alto Índice final del subarreglo.
 */
void quickSort(vector<int>& arreglo, int bajo, int alto) {
    if (bajo < alto) {
        // Obtener el índice del pivote después de la partición
        int pi = particion(arreglo, bajo, alto);
        
        // Ordenar las partes izquierda y derecha del pivote
        quickSort(arreglo, bajo, pi - 1);
        quickSort(arreglo, pi + 1, alto);
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
        descripcion = "dataset aleatorio ";
    } else if (nombreArchivo.find("parcialmente_ordenado") != string::npos) {
        descripcion = "dataset parcialmente ordenado ";
    } else if (nombreArchivo.find("ordenado") != string::npos) {
        descripcion = "dataset ordenado ";
    }

    // Determinar el tamaño del dataset según el nombre del archivo
    if (nombreArchivo.find("100000") != string::npos) {
        descripcion += "de 100000 elementos";
    } else if (nombreArchivo.find("10000") != string::npos) {
        descripcion += "de 10000 elementos";
    } else if (nombreArchivo.find("1000") != string::npos) {
        descripcion += "de 1000 elementos";
    }

    return descripcion;
}

/**
 * @brief Mide el tiempo de ejecución del algoritmo Quick Sort y muestra el resultado.
 * 
 * @param nombreArchivo Nombre del archivo del dataset.
 * @param datos Vector que contiene el dataset a ordenar.
 */
void medirTiempo(const string& nombreArchivo, vector<int>& datos) {
    string descripcionDataset = obtenerDescripcionDataset(nombreArchivo);

    // Medir el tiempo de ejecución del algoritmo de ordenamiento
    auto inicio = chrono::high_resolution_clock::now();
    quickSort(datos, 0, datos.size() - 1);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    // Mostrar el tiempo de ejecución en milisegundos
    cout << "Quick Sort de " << descripcionDataset << " - Tiempo: " << duracion.count() << " ms" << endl;

    // Opción de depuración: imprimir los primeros 10 elementos ordenados
    /*
    cout << "Primeros 10 elementos ordenados: ";
    for (int i = 0; i < min(10, (int)datos.size()); ++i) {
        cout << datos[i] << " ";
    }
    cout << endl;
    */
}

/**
 * @brief Función principal que lee datasets desde archivos y mide el tiempo de ordenamiento usando Quick Sort.
 * 
 * @return int Código de estado de la ejecución.
 */
int main() {
    // Semilla para la función rand() basada en el tiempo actual para obtener diferentes pivotes aleatorios
    srand(time(0));

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
