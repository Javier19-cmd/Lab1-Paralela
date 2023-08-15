/**
 * @file piSeriesNaive2.c
 * @author Javier Valle, Mario de León
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


/**
 * 1. Este codigo consiste en una logica paralela en donde siempre existe una cantidad N de iteraciones.
 * Una cantidad de hilos (que se puede modificar medida que se necesite), un factor que ayuda a calcular pi.
 * la variable que almacena la suma y la aproximacion de pi.
 * 2. Por otro lado, se hacen varias mediciones para calcular de manera mas exacta el valor de pi y existe una variable
 *    que almacena el tiempo que se invirtio en la suma.
 * 3. En este codigo se implemento una parte paralela con la clausula de reduccion para optimizar los calculos.
 * 4. Se puede notar tambien que se calcula el tiempo total de ejecucion del programa. 
 * 5. Finalmente, se imprime el valor aproximado de pi y el tiempo que tomo hacerlo. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000000; // N.
    int thread_count = 15; // Cantidad de hilos.
    double sum = 0.0;
    double pi_approx;

    // Realizando varias mediciones.
    int num_measurements = 15;
    double total_time = 0.0;

    for (int measurement = 0; measurement < num_measurements; measurement++) {
        double start_time = omp_get_wtime();

        #pragma omp parallel for num_threads(thread_count) reduction(+:sum)
        for (int k = 0; k < n; k++) {
            double factor;
            if (k % 2 == 0)
                factor = 1.0;
            else
                factor = -1.0;

            sum += factor / (2 * k + 1);
        }

        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;
        total_time += elapsed_time;
    }

    pi_approx = 4.0 * sum;

    printf("Valor aproximado de pi: %lf\n", pi_approx);
    printf("Tiempo promedio de ejecución: %lf segundos\n", total_time / num_measurements);

    return 0;
}