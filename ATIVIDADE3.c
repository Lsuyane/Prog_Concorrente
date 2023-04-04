
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    printf("ola\n\n");

    int num_steps=300000000;
    double step;
    int i; double x, pi, sum = 0.0;
    int t = omp_get_num_threads();

    printf("Theads: %d\n",t);
    double inicio = omp_get_wtime();
    step = 1.0/(double)num_steps;

    for (i=0;i< num_steps; i++){
        x = (i + 0.5) * step; 
        sum = sum + 4.0 / (1.0 + x*x);
    }
    pi = step * sum;

    double fim = omp_get_wtime();
    printf("S_Pi: %f\n",pi);
    double seq = fim-inicio;
    printf("Execucao sequencial(s): %f\n",seq);
    
//P
    x = 0; pi = 0; sum = 0;
    inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    #pragma omp parallel num_threads(5)
    {
        double sum = 0.0;
        double x;
        #pragma omp for
        for (i=0;i< num_steps; i++){
            x = (i + 0.5) * step; 
            sum = sum + 4.0 / (1.0 + x*x);  
        }
       #pragma omp atomic
       pi = pi + (step * sum);
        printf("ATOMIC pi: %f\n", pi);
    } 
   

    fim = omp_get_wtime();
    printf("P_Pi: %f\n",pi);
    double time = fim-inicio;
    printf("Execucao paralela(s): %f\n",time);
   

    return 0;

}
