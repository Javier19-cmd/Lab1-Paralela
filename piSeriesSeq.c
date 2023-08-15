/**
 * @file piSeriesSeq.c
 * @author Javier Valle, Mario de León
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 /**
 * Programa secuencial que calcula el valor de pi.
 * factor es un termino que ayuda a calcular la aprox. de pi.
 * sum es la suma iterativa que se va haciendo a lo largo de la serie.
 * pi_approx es el valor final que se obtiene luego de haber hecho las iteraciones de la serie. 
 */

#include <stdio.h>

int main() {
    int n = 1000; // Valor de iteraciones.
    double factor = 1.0;
    double sum = 0.0;
    
    for (int k = 0; k < n; k++) {
        sum += factor / (2 * k + 1);
        factor = -factor;
    }
    
    double pi_approx = 4.0 * sum;
    
    printf("Valor aproximado de pi: %lf\n", pi_approx);
    
    return 0;
}
