/**
 * @file piSeriesImproved.c
 * @author Javier Valle, Mario de León
 * @brief
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

double calcularPI_original(int n, int threads)
{
    double sum = 0.0;
    double factor;

#pragma omp parallel for num_threads(threads) reduction(+ : sum) private(factor) schedule(dynamic, 128)
    for (int k = 0; k < n; k++)
    {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }

    return 4.0 * sum;
}

double calcularPI_alternativo(int n, int threads)
{
    double sum_even = 0.0;
    double sum_odd = 0.0;

#pragma omp parallel for num_threads(threads) reduction(+ : sum_even)
    for (int i = 0; i < n; i += 2)
    {
        sum_even += 1.0 / (2 * i + 1);
    }

#pragma omp parallel for num_threads(threads) reduction(+ : sum_odd)
    for (int j = 1; j < n; j += 2)
    {
        sum_odd += 1.0 / (2 * j + 1);
    }

    return 4.0 * (sum_even - sum_odd);
}

int main()
{
    const int n = 10000000; // 10e6
    const int threads = omp_get_num_procs();
    const double PI = 3.14159265358979323846;

    for (int run = 1; run <= 5; run++)
    {
        printf("Run %d:\n", run);

        double inicio, fin, pi_aprox;

        // Método original
        inicio = omp_get_wtime();
        pi_aprox = calcularPI_original(n, threads);
        fin = omp_get_wtime();
        printf("Método Original:\n");
        printf("Tiempo de ejecución: %lf segundos\n", fin - inicio);
        printf("PI aproximado: %lf\n", pi_aprox);
        printf("Error: %lf%%\n\n", 100.0 * fabs(pi_aprox - PI) / PI);

        // Método alternativo
        inicio = omp_get_wtime();
        pi_aprox = calcularPI_alternativo(n, threads);
        fin = omp_get_wtime();
        printf("Método Alternativo:\n");
        printf("Tiempo de ejecución: %lf segundos\n", fin - inicio);
        printf("PI aproximado: %lf\n", pi_aprox);
        printf("Error: %lf%%\n", 100.0 * fabs(pi_aprox - PI) / PI);

        printf("\n====================================\n\n");
    }

    return 0;
}
