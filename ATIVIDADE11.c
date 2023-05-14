#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //SERIAL  
    printf("ola\n\n");

    int num_steps=100000000;
    double step;
    int i; double x, pi, pi_total, sum = 0.0;
    step = 1.0/(double)num_steps;

    for (i=rank;i<=num_steps;i+=nprocs) {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;
    MPI_Reduce(&pi,&pi_total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if (rank==0) {
        printf("Valor de pi: %.10f\n",pi_total);
    }

    MPI_Finalize();
    return 0;
}
