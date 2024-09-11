#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Leer una matriz desde un archivo
vector<vector<int>> leerMatrizDesdeArchivo(const string& nombreArchivo, int filas, int columnas) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    ifstream archivo(nombreArchivo);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo >> matriz[i][j];
        }
    }
    archivo.close();
    return matriz;
}

// Algoritmo de multiplicación cúbica tradicional
vector<vector<int>> multiplicarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int filasA, int columnasA, int columnasB) {
    vector<vector<int>> C(filasA, vector<int>(columnasB, 0));
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            for (int k = 0; k < columnasA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Medir y mostrar el tiempo
void medirTiempo(const string& nombreMatrizA, const string& nombreMatrizB, int filasA, int columnasA, int columnasB) {
    vector<vector<int>> A = leerMatrizDesdeArchivo(nombreMatrizA, filasA, columnasA);
    vector<vector<int>> B = leerMatrizDesdeArchivo(nombreMatrizB, columnasA, columnasB);

    auto inicio = chrono::high_resolution_clock::now();
    vector<vector<int>> C = multiplicarMatrices(A, B, filasA, columnasA, columnasB);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    cout << "Multiplicacion Tradicional de " << filasA << "x" << columnasA << " y " << columnasA << "x" << columnasB 
        << " - Tiempo: " << duracion.count() << " ms" << endl;
}

int main() {
    // Multiplicación de matrices cuadradas
    medirTiempo("matriz_100x100.txt", "matriz_100x100.txt", 100, 100, 100);
    medirTiempo("matriz_500x500.txt", "matriz_500x500.txt", 500, 500, 500);
    medirTiempo("matriz_1000x1000.txt", "matriz_1000x1000.txt", 1000, 1000, 1000);

    // Multiplicación de matrices no cuadradas
    medirTiempo("matriz_100x500.txt", "matriz_500x1000.txt", 100, 500, 1000);

    return 0;
}
