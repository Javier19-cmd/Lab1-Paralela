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

#define PI 3.14159265358979323846

int main()
{
    int n = 10000000; // n = 10e6
    int cores = omp_get_num_procs();
    double sum_even = 0.0;
    double sum_odd = 0.0;
    double pi_approx;

    // Nota: Al usar omp_get_wtime(), estamos midiendo el tiempo de wall-clock y no el tiempo de CPU.
    double start_time = omp_get_wtime();

#pragma omp parallel for num_threads(cores) reduction(+ : sum_even)
    for (int i = 0; i < n; i += 2)
    {
        sum_even += 1.0 / (2.0 * i + 1);
    }

#pragma omp parallel for num_threads(cores) reduction(+ : sum_odd)
    for (int j = 1; j < n; j += 2)
    {
        sum_odd += 1.0 / (2.0 * j + 1);
    }

    pi_approx = 4.0 * (sum_even - sum_odd);
    double elapsed_time = omp_get_wtime() - start_time;

    double error_percentage = (fabs(pi_approx - PI) / PI) * 100;

    printf("Tiempo de ejecución: %lf segundos\n", elapsed_time);
    printf("Aproximación de PI: %.15lf\n", pi_approx);
    printf("Porcentaje de error con respecto a PI: %.5lf%%\n", error_percentage);

    return 0;
}
