#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int crivoSeq(int n, double *tempo) {
    int *primos = (int*)malloc((n+1) * sizeof(int));
    
    double t_inicio, t_final;
    int raiz = sqrt(n);

    t_inicio = omp_get_wtime();

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
    int true=0;
    int qtdPrim = 0;
    for (int i = 0; i <= n; i++){
        if (primos[i] == 1){
            qtdPrim++;
        }   
    }        
    
    printf("Numero primos encontrados (sequencial): %d\n", qtdPrim);
    t_final = omp_get_wtime();
   *tempo = t_final - t_inicio;
    free(primos);

    return true;
}

int main () {
    double tempo;
    int n = 10000000;
    printf("Números primos até %d:\n\n", n);

    for(int i = 0; i < 10; i++) {
        if (crivoSeq(n, &tempo)!=0)
            break;

    printf("Tempo sequencial: %f\n\n", tempo);
  }
  return 0;
}