#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>


void crivoMPI(int rank, int nprocs, int tamanho) {
    double inicio_proc, fim_proc, tempo_proc;
    int i;
    int pulo;
    pulo = tamanho / nprocs;
    int *primo = NULL;
    int raiz = (sqrt(tamanho));

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        inicio_proc = MPI_Wtime();
    }

    primo = (int *)malloc(tamanho * sizeof(int));

    for (int i = 0; i < pulo; i++) {
        primo[i] = 1;
    }

    for (int i = 2; i < raiz; i++) {
        if (primo[i] == 1) {
            for (int j = i * i; j < pulo; j += i) {
                primo[j] = 0;
            }
        }
    }

    
    if (rank == 0) {
        fim_proc = MPI_Wtime();
        tempo_proc = fim_proc - inicio_proc;
        int count = 0;
        int totalPrimos = 0;

        for (i = 2; i < tamanho; i++) {
            if (primo[i] == 1) {
                totalPrimos++;
            }
        }
        printf("Tempo de processamento: %f\n", tempo_proc);
        printf("Quantidade de primos encontrados: %d\n", totalPrimos);

    }

    free(primo);
}

int main() {
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int tamanho = 100000000;

    crivoMPI(rank, nprocs, tamanho);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
