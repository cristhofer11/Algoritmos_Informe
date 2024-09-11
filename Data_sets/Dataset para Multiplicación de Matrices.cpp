#include <iostream>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

/**
 * @brief Genera una matriz aleatoria de tamaño filas x columnas con valores entre 0 y 100.
 * 
 * @param filas Número de filas de la matriz.
 * @param columnas Número de columnas de la matriz.
 * @return vector<vector<int>> Matriz generada aleatoriamente.
 */
vector<vector<int>> generarMatrizAleatoria(int filas, int columnas) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    
    // Generador de números aleatorios
    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<> distribucion(0, 100); // Valores aleatorios entre 0 y 100

    // Llenar la matriz con valores aleatorios
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = distribucion(generador);
        }
    }

    return matriz;
}

/**
 * @brief Guarda una matriz en un archivo de texto.
 * 
 * @param matriz Matriz que se desea guardar.
 * @param nombreArchivo Nombre del archivo donde se guardará la matriz.
 */
void guardarMatrizEnArchivo(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    // Guardar cada fila de la matriz en el archivo
    for (const auto& fila : matriz) {
        for (int valor : fila) {
            archivo << valor << " ";  // Separar los valores por espacios
        }
        archivo << "\n";  // Nueva línea después de cada fila
    }

    archivo.close();
}

/**
 * @brief Función principal que genera matrices aleatorias y las guarda en archivos de texto.
 * 
 * @return int Código de estado de la ejecución.
 */
int main() {
    // Generar matrices cuadradas
    vector<vector<int>> matriz100x100 = generarMatrizAleatoria(100, 100);
    vector<vector<int>> matriz500x500 = generarMatrizAleatoria(500, 500);
    vector<vector<int>> matriz1000x1000 = generarMatrizAleatoria(1000, 1000);

    // Generar matrices no cuadradas
    vector<vector<int>> matriz100x500 = generarMatrizAleatoria(100, 500);
    vector<vector<int>> matriz500x1000 = generarMatrizAleatoria(500, 1000);

    // Guardar las matrices en archivos de texto
    guardarMatrizEnArchivo(matriz100x100, "matriz_100x100.txt");
    guardarMatrizEnArchivo(matriz500x500, "matriz_500x500.txt");
    guardarMatrizEnArchivo(matriz1000x1000, "matriz_1000x1000.txt");

    guardarMatrizEnArchivo(matriz100x500, "matriz_100x500.txt");
    guardarMatrizEnArchivo(matriz500x1000, "matriz_500x1000.txt");

    // Mostrar mensaje de confirmación
    cout << "Matrices generadas y guardadas." << endl;

    return 0;
}
