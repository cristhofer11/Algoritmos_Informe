#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

/**
 * @brief Genera un dataset aleatorio de tamaño especificado.
 * 
 * @param tamano Tamaño del dataset a generar.
 * @return vector<int> Dataset generado aleatoriamente.
 */
vector<int> generarDatasetAleatorio(int tamano) {
    vector<int> dataset(tamano);

    // Generador de números aleatorios
    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<> distribucion(0, tamano);  // Números entre 0 y el tamaño

    // Llenar el dataset con valores aleatorios
    for (int i = 0; i < tamano; i++) {
        dataset[i] = distribucion(generador);
    }

    return dataset;
}

/**
 * @brief Genera un dataset parcialmente ordenado donde la mitad del dataset está ordenada.
 * 
 * @param tamano Tamaño del dataset a generar.
 * @return vector<int> Dataset parcialmente ordenado.
 */
vector<int> generarDatasetParcialmenteOrdenado(int tamano) {
    vector<int> dataset = generarDatasetAleatorio(tamano);

    // Ordenar la mitad del dataset
    sort(dataset.begin(), dataset.begin() + tamano / 2);

    return dataset;
}

/**
 * @brief Genera un dataset completamente ordenado.
 * 
 * @param tamano Tamaño del dataset a generar.
 * @return vector<int> Dataset completamente ordenado.
 */
vector<int> generarDatasetOrdenado(int tamano) {
    vector<int> dataset = generarDatasetAleatorio(tamano);

    // Ordenar completamente el dataset
    sort(dataset.begin(), dataset.end());

    return dataset;
}

/**
 * @brief Guarda un dataset en un archivo de texto.
 * 
 * @param dataset Dataset que se desea guardar.
 * @param nombreArchivo Nombre del archivo donde se guardará el dataset.
 */
void guardarDatasetEnArchivo(const vector<int>& dataset, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    // Guardar cada valor del dataset en el archivo
    for (int numero : dataset) {
        archivo << numero << "\n";  // Cada número en una nueva línea
    }

    archivo.close();
}

/**
 * @brief Función principal que genera datasets de diferentes tamaños y los guarda en archivos de texto.
 * 
 * @return int Código de estado de la ejecución.
 */
int main() {
    // Tamaños de los datasets
    int tamano1000 = 1000;
    int tamano10000 = 10000;
    int tamano100000 = 100000;

    // Generar datasets de 1000 elementos
    vector<int> datasetAleatorio1000 = generarDatasetAleatorio(tamano1000);
    vector<int> datasetParcialmenteOrdenado1000 = generarDatasetParcialmenteOrdenado(tamano1000);
    vector<int> datasetOrdenado1000 = generarDatasetOrdenado(tamano1000);

    // Generar datasets de 10000 elementos
    vector<int> datasetAleatorio10000 = generarDatasetAleatorio(tamano10000);
    vector<int> datasetParcialmenteOrdenado10000 = generarDatasetParcialmenteOrdenado(tamano10000);
    vector<int> datasetOrdenado10000 = generarDatasetOrdenado(tamano10000);

    // Generar datasets de 100000 elementos
    vector<int> datasetAleatorio100000 = generarDatasetAleatorio(tamano100000);
    vector<int> datasetParcialmenteOrdenado100000 = generarDatasetParcialmenteOrdenado(tamano100000);
    vector<int> datasetOrdenado100000 = generarDatasetOrdenado(tamano100000);

    // Guardar los datasets en archivos
    guardarDatasetEnArchivo(datasetAleatorio1000, "dataset_aleatorio_1000.txt");
    guardarDatasetEnArchivo(datasetParcialmenteOrdenado1000, "dataset_parcialmente_ordenado_1000.txt");
    guardarDatasetEnArchivo(datasetOrdenado1000, "dataset_ordenado_1000.txt");

    guardarDatasetEnArchivo(datasetAleatorio10000, "dataset_aleatorio_10000.txt");
    guardarDatasetEnArchivo(datasetParcialmenteOrdenado10000, "dataset_parcialmente_ordenado_10000.txt");
    guardarDatasetEnArchivo(datasetOrdenado10000, "dataset_ordenado_10000.txt");

    guardarDatasetEnArchivo(datasetAleatorio100000, "dataset_aleatorio_100000.txt");
    guardarDatasetEnArchivo(datasetParcialmenteOrdenado100000, "dataset_parcialmente_ordenado_100000.txt");
    guardarDatasetEnArchivo(datasetOrdenado100000, "dataset_ordenado_100000.txt");

    // Mostrar mensaje de confirmación
    cout << "Datasets generados y guardados." << endl;

    return 0;
}
