#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#define THREADS 3

int crivoMP(int n, double *tempoPar) {
    int *primos = (int*)calloc(n, sizeof(int));
    
    double t_inicio, t_final;
    int raiz = sqrt(n);
    int threads[THREADS];

    t_inicio = omp_get_wtime();
    #pragma omp parallel num_threads(THREADS)
    {
        int n_threads = omp_get_thread_num();

        #pragma omp for
        for(int p = 2; p < n; p++) {
            primos[p] = 1;
        }
        
        for(int p = 2; p * p < n; p++) {
            if (primos[p] == 1) {
                for(int i = p * p; i < n;i += p) {
                    primos[i] = 0;
                }
            }
        }
        threads[n_threads] = 0;
        #pragma omp for
        for (int p = 0; p < n; p++) {
            if (primos[p] == 1) {
                threads[n_threads]++;
            }
        }
    }
    int total_primos = 0;
    for (int i = 0; i < THREADS; i++){
        total_primos += threads[i];   
    }        
    
    t_final = omp_get_wtime();
    *tempoPar = t_final - t_inicio;

    free(primos);
    printf("Numero primos encontrados (paralelo): %d\n", total_primos);
    return 0;
}

int main () {
    double tempoSeq, tempoPar;
    int n = 10000000;
    printf("Números primos até %d:\n\n", n);

    for(int i = 0; i < 10; i++) {
    if (crivoMP(n, &tempoPar)!=0) 
      break;

    printf("Tempo paralelo  : %.3f\n", tempoPar);
  }
/*
    double speedup = tempoSeq / tempoPar;
    printf("Speedup: %f\n", speedup);
*/
    return 0;
}
