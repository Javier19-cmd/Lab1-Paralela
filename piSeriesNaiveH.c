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
    int n = 10000000; // 10e6
    int cores = omp_get_num_procs();
    double sum;
    double pi_approx;
    double sequential_time, parallel_time;

    // Tiempo secuencial (threads = 1)
    sum = 0.0;
    double start_time = omp_get_wtime();
    for (int k = 0; k < n; k++)
    {
        double factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }
    sequential_time = omp_get_wtime() - start_time;

    printf("Tiempo secuencial: %lf segundos\n", sequential_time);
    printf("\nScheduling\tBlock Size\tRun\tParallel Time\tSpeedup\n");
    printf("------------------------------------------------------------\n");

    char *schedules[] = {"static", "dynamic", "guided", "auto"};
    int block_sizes[] = {16, 64, 128};
    int num_schedules = sizeof(schedules) / sizeof(schedules[0]);
    int num_block_sizes = sizeof(block_sizes) / sizeof(block_sizes[0]);

    for (int s = 0; s < num_schedules; s++)
    {
        if (s != 3) // Excluir "auto" de los block_sizes
        {
            for (int b = 0; b < num_block_sizes; b++)
            {
                for (int run = 1; run <= 5; run++)
                {
                    sum = 0.0;
                    start_time = omp_get_wtime();
#pragma omp parallel for num_threads(cores) reduction(+ : sum) schedule(static, block_sizes[b])
                    for (int k = 0; k < n; k++)
                    {
                        double factor = (k % 2 == 0) ? 1.0 : -1.0;
                        sum += factor / (2 * k + 1);
                    }
                    parallel_time = omp_get_wtime() - start_time;
                    double speedup = sequential_time / parallel_time;

                    printf("%s\t%d\t\t%d\t%lf\t%lf\n", schedules[s], block_sizes[b], run, parallel_time, speedup);
                }
            }
        }
        else // Para "auto"
        {
            for (int run = 1; run <= 5; run++)
            {
                sum = 0.0;
                start_time = omp_get_wtime();
#pragma omp parallel for num_threads(cores) reduction(+ : sum) schedule(auto)
                for (int k = 0; k < n; k++)
                {
                    double factor = (k % 2 == 0) ? 1.0 : -1.0;
                    sum += factor / (2 * k + 1);
                }
                parallel_time = omp_get_wtime() - start_time;
                double speedup = sequential_time / parallel_time;

                printf("%s\t\t%d\t%lf\t%lf\n", schedules[s], run, parallel_time, speedup);
            }
        }
    }

    return 0;
}