# Algoritmos de Evaluación Experimental

Este proyecto contiene la implementación y evaluación experimental de varios algoritmos de **ordenamiento** y **multiplicación de matrices** en C++. El objetivo es comparar el rendimiento de estos algoritmos con las funciones provistas por la biblioteca estándar de C++.

## Estructura del Proyecto

- **Ordenamiento** (`Ordenamiento/`):
  - `selection_sort.cpp`: Implementación de Selection Sort.
  - `mergesort.cpp`: Implementación de Mergesort.
  - `quicksort.cpp`: Implementación de Quicksort.
  - `std_sort.cpp`: Uso de `std::sort()`.

- **Multiplicación de Matrices** (`Multiplicación de Matrices/`):
  - `tradicional.cpp`: Implementación del algoritmo cúbico tradicional.
  - `optimizado.cpp`: Algoritmo cúbico optimizado (localidad de datos).
  - `strassen.cpp`: Implementación del algoritmo de Strassen.

- **Generación de Datasets** (`datasets/`):
  - `generate_datasets.cpp`: Script para generar los datasets de prueba.

## Cómo Ejecutar

1. **Clonar el Repositorio**:
   ```bash
   git clone https://github.com/cristhofer11/Algoritmos_Informe.git
   cd Algoritmos_Informe
