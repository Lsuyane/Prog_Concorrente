#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAM 1000

int main(int argc, char** argv) {
    int rank, size;
    int data[TAM];
    int subTotal = 0, total = 0, subTotalD = 0, totalD = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < TAM; ++i) {
            data[i] = rand() % 100;
        }
        MPI_Bcast(data, TAM, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(data, TAM, MPI_INT, 0, MPI_COMM_WORLD);
    }
    for (int i = 0; i < TAM; ++i) {
        subTotal += data[i];
        subTotalD += data[i] * 2;
    }
    MPI_Reduce(&subTotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&subTotalD, &totalD, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultado do somatório: %d\n", total);
        printf("Resultado do somatório dobro: %d\n", totalD);
    }
    MPI_Finalize();
    return 0;
}
