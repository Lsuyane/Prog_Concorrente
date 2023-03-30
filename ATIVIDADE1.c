#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
//S
    printf("ola");

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
    printf("%.5f\n",pi);
    double t_serial = fim-inicio;
    printf("Execucao sequencial(s): %f\n",t_serial);
    
//P
    x = 0; pi = 0; sum = 0;
    inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    #pragma omp parallel private(x) num_threads(5)
    {
        #pragma omp for reduction (+:sum)
        for (i=0;i< num_steps; i++){
            x = (i + 0.5) * step; 
            sum = sum + 4.0 / (1.0 + x*x);  
        }
    } 
    pi = step * sum;

    double fim = omp_get_wtime();
    printf("%.5f\n",pi);
    double t_paralelo = fim-inicio;
    double speedup = t_serial/t_paralelo;
    printf("Pi: %f\n",pi);
    printf("Execucao paralela(s): %f\n",t_paralelo);
    printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n",speedup/4.0);

    return 0;

}
