#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAMANHO 1000000

int main(){
  
    int i;
    double start_time, end_time;
    double *vetor;
    double maior = 0.0;
    vetor = (double *) malloc(sizeof(double) * TAMANHO);

    #pragma omp parallel for
    for(i = 0; i < TAMANHO; i++) {
        vetor[i] = (double) rand() / RAND_MAX;
    }
    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(max:maior)
    for(i = 0; i < TAAMANHO; i++) {
        if(vetor[i] > maior) {
            maior = vetor[i];
        }
    }

    end_time = omp_get_wtime();

    printf("Maior valor do vetor: %f\n", maior);
    printf("Tempo de execução: %f \n", end_time - start_time);

    free(vetor);

    return 0;
}

