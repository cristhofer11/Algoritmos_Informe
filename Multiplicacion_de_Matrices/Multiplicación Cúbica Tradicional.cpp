#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

/**
 * @brief Lee una matriz desde un archivo y la carga en una estructura vectorial 2D.
 * 
 * @param nombreArchivo Nombre del archivo que contiene la matriz.
 * @param filas Número de filas de la matriz.
 * @param columnas Número de columnas de la matriz.
 * @return vector<vector<int>> Matriz leída desde el archivo.
 */
vector<vector<int>> leerMatrizDesdeArchivo(const string& nombreArchivo, int filas, int columnas) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    ifstream archivo(nombreArchivo);
    
    // Leer los datos desde el archivo y almacenarlos en la matriz
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo >> matriz[i][j];
        }
    }

    archivo.close();
    return matriz;
}

/**
 * @brief Implementa el algoritmo de multiplicación cúbica tradicional de dos matrices.
 * 
 * @param A Primera matriz.
 * @param B Segunda matriz.
 * @param filasA Número de filas de la matriz A.
 * @param columnasA Número de columnas de la matriz A (y filas de la matriz B).
 * @param columnasB Número de columnas de la matriz B.
 * @return vector<vector<int>> Matriz resultante de la multiplicación.
 */
vector<vector<int>> multiplicarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int filasA, int columnasA, int columnasB) {
    // Inicializar la matriz de resultado con ceros
    vector<vector<int>> C(filasA, vector<int>(columnasB, 0));

    // Realizar la multiplicación de matrices
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            for (int k = 0; k < columnasA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

/**
 * @brief Mide el tiempo de ejecución de la multiplicación de dos matrices y muestra el resultado.
 * 
 * @param nombreMatrizA Nombre del archivo que contiene la primera matriz.
 * @param nombreMatrizB Nombre del archivo que contiene la segunda matriz.
 * @param filasA Número de filas de la primera matriz.
 * @param columnasA Número de columnas de la primera matriz (y filas de la segunda matriz).
 * @param columnasB Número de columnas de la segunda matriz.
 */
void medirTiempo(const string& nombreMatrizA, const string& nombreMatrizB, int filasA, int columnasA, int columnasB) {
    // Leer las matrices desde los archivos
    vector<vector<int>> A = leerMatrizDesdeArchivo(nombreMatrizA, filasA, columnasA);
    vector<vector<int>> B = leerMatrizDesdeArchivo(nombreMatrizB, columnasA, columnasB);

    // Medir el tiempo de ejecución de la multiplicación
    auto inicio = chrono::high_resolution_clock::now();
    vector<vector<int>> C = multiplicarMatrices(A, B, filasA, columnasA, columnasB);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    // Mostrar el tiempo de ejecución
    cout << "Multiplicación Tradicional de " << filasA << "x" << columnasA << " y " 
         << columnasA << "x" << columnasB << " - Tiempo: " << duracion.count() << " ms" << endl;
}

/**
 * @brief Función principal que realiza la multiplicación de matrices y mide el tiempo de ejecución.
 * 
 * @return int Código de estado de la ejecución.
 */
int main() {
    // Multiplicación de matrices cuadradas
    medirTiempo("matriz_100x100.txt", "matriz_100x100.txt", 100, 100, 100);
    medirTiempo("matriz_500x500.txt", "matriz_500x500.txt", 500, 500, 500);
    medirTiempo("matriz_1000x1000.txt", "matriz_1000x1000.txt", 1000, 1000, 1000);

    // Multiplicación de matrices no cuadradas
    medirTiempo("matriz_100x500.txt", "matriz_500x1000.txt", 100, 500, 1000);

    return 0;
}
