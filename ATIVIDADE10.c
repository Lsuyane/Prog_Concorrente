//MPI PI
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

//MPI Send Recv
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int data_send = 42;
    int data_recv;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        MPI_Send(&data_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(&data_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu o valor: %d\n", rank, data_recv);
    }

    MPI_Finalize();
    return 0;
}
