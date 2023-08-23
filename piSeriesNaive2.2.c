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

int main()
{
    int n = 1000000;
    int cores = omp_get_num_procs();
    double sum;
    double pi_approx;

    printf("Run\tSecuencial\tParalelo (cores)\tParalelo (2*cores)\tParalelo (n*10 & cores)\n");
    printf("------------------------------------------------------------------------------------\n");

    for (int run = 1; run <= 5; run++)
    {
        double sequential_time, parallel_time_cores, parallel_time_2cores, parallel_time_increased_n;

        // Tiempo secuencial (threads = 1)
        sum = 0.0;
        double start_time = omp_get_wtime();
        for (int k = 0; k < n; k++)
        {
            double factor = (k % 2 == 0) ? 1.0 : -1.0;
            sum += factor / (2 * k + 1);
        }
        sequential_time = omp_get_wtime() - start_time;

        // Tiempo paralelo (threads = cores)
        sum = 0.0;
        start_time = omp_get_wtime();
#pragma omp parallel for num_threads(cores) reduction(+ : sum)
        for (int k = 0; k < n; k++)
        {
            double factor = (k % 2 == 0) ? 1.0 : -1.0;
            sum += factor / (2 * k + 1);
        }
        parallel_time_cores = omp_get_wtime() - start_time;

        // Tiempo paralelo (threads = 2 * cores)
        sum = 0.0;
        start_time = omp_get_wtime();
#pragma omp parallel for num_threads(2 * cores) reduction(+ : sum)
        for (int k = 0; k < n; k++)
        {
            double factor = (k % 2 == 0) ? 1.0 : -1.0;
            sum += factor / (2 * k + 1);
        }
        parallel_time_2cores = omp_get_wtime() - start_time;

        // Tiempo paralelo (n = n*10 && threads = cores)
        int increased_n = n * 10;
        sum = 0.0;
        start_time = omp_get_wtime();
#pragma omp parallel for num_threads(cores) reduction(+ : sum)
        for (int k = 0; k < increased_n; k++)
        {
            double factor = (k % 2 == 0) ? 1.0 : -1.0;
            sum += factor / (2 * k + 1);
        }
        parallel_time_increased_n = omp_get_wtime() - start_time;

        printf("%d\t%lf\t%lf\t%lf\t%lf\n", run, sequential_time, parallel_time_cores, parallel_time_2cores, parallel_time_increased_n);
    }

    return 0;
}
