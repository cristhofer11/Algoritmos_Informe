#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

const int UMBRAL = 64;  // Umbral para usar multiplicación tradicional en vez de Strassen

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
 * @brief Suma dos matrices del mismo tamaño.
 * 
 * @param A Primera matriz.
 * @param B Segunda matriz.
 * @return vector<vector<int>> Matriz resultante de la suma.
 */
vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    
    return C;
}

/**
 * @brief Resta dos matrices del mismo tamaño.
 * 
 * @param A Primera matriz.
 * @param B Segunda matriz.
 * @return vector<vector<int>> Matriz resultante de la resta.
 */
vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    
    return C;
}

/**
 * @brief Multiplicación tradicional (cúbica) de dos matrices.
 * 
 * @param A Primera matriz.
 * @param B Segunda matriz.
 * @return vector<vector<int>> Matriz resultante de la multiplicación tradicional.
 */
vector<vector<int>> multiplicarMatricesCubic(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    // Multiplicación cúbica estándar
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

/**
 * @brief Implementa el algoritmo de multiplicación de matrices de Strassen con un umbral.
 * 
 * @param A Primera matriz.
 * @param B Segunda matriz.
 * @return vector<vector<int>> Matriz resultante de la multiplicación.
 */
vector<vector<int>> strassenMultiplicacion(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Si la matriz es lo suficientemente pequeña, usar multiplicación tradicional
    if (n <= UMBRAL) {
        return multiplicarMatricesCubic(A, B);
    }

    int nuevoTamano = n / 2;

    // Inicialización de submatrices
    vector<vector<int>> A11(nuevoTamano, vector<int>(nuevoTamano)), A12(nuevoTamano, vector<int>(nuevoTamano)),
        A21(nuevoTamano, vector<int>(nuevoTamano)), A22(nuevoTamano, vector<int>(nuevoTamano)),
        B11(nuevoTamano, vector<int>(nuevoTamano)), B12(nuevoTamano, vector<int>(nuevoTamano)),
        B21(nuevoTamano, vector<int>(nuevoTamano)), B22(nuevoTamano, vector<int>(nuevoTamano));

    // Dividir las matrices A y B en submatrices
    for (int i = 0; i < nuevoTamano; i++) {
        for (int j = 0; j < nuevoTamano; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + nuevoTamano];
            A21[i][j] = A[i + nuevoTamano][j];
            A22[i][j] = A[i + nuevoTamano][j + nuevoTamano];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + nuevoTamano];
            B21[i][j] = B[i + nuevoTamano][j];
            B22[i][j] = B[i + nuevoTamano][j + nuevoTamano];
        }
    }

    // Calcular los productos de Strassen
    vector<vector<int>> M1 = strassenMultiplicacion(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    vector<vector<int>> M2 = strassenMultiplicacion(sumarMatrices(A21, A22), B11);
    vector<vector<int>> M3 = strassenMultiplicacion(A11, restarMatrices(B12, B22));
    vector<vector<int>> M4 = strassenMultiplicacion(A22, restarMatrices(B21, B11));
    vector<vector<int>> M5 = strassenMultiplicacion(sumarMatrices(A11, A12), B22);
    vector<vector<int>> M6 = strassenMultiplicacion(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    vector<vector<int>> M7 = strassenMultiplicacion(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Calcular las submatrices de la matriz resultante C
    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    // Unir las submatrices en la matriz resultante
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < nuevoTamano; i++) {
        for (int j = 0; j < nuevoTamano; j++) {
            C[i][j] = C11[i][j];
            C[i][j + nuevoTamano] = C12[i][j];
            C[i + nuevoTamano][j] = C21[i][j];
            C[i + nuevoTamano][j + nuevoTamano] = C22[i][j];
        }
    }

    return C;
}

/**
 * @brief Mide el tiempo de ejecución del algoritmo de Strassen y muestra el resultado.
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

    // Medir el tiempo de ejecución de Strassen
    auto inicio = chrono::high_resolution_clock::now();
    vector<vector<int>> C = strassenMultiplicacion(A, B);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    // Mostrar el tiempo de ejecución
    cout << "Strassen de " << filasA << "x" << columnasA << " y " 
         << columnasA << "x" << columnasB << " - Tiempo: " << duracion.count() << " ms" << endl;
}

/**
 * @brief Función principal que realiza la multiplicación de matrices con el algoritmo de Strassen.
 * 
 * @return int Código de estado de la ejecución.
 */
int main() {
    // Multiplicación de matrices cuadradas y no cuadradas
    medirTiempo("matriz_100x100.txt", "matriz_100x100.txt", 100, 100, 100);
    medirTiempo("mat
