#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAMANHO 10000

int *gerar_vetor_aleatorio(int n) {
    int *vetor;
    int i;
    vetor = (int *) malloc(sizeof(int)*n);
    for (int i=0;i<n;i++) {
        int num = rand ()% 2;
        vetor[i] = num;
    }
    return vetor;
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char process_name[MPI_MAX_PROCESSOR_NAME];
    int name;
    MPI_Get_processor_name(process_name, &name);
    time_t t;
    srand((unsigned) time(&t)*rank);
    int subtamanho = (int)(TAMANHO/nprocs);
    int *subvetor = NULL;
    subvetor = gerar_vetor_aleatorio(subtamanho);

    int soma = 0;
    for (int i=0;i<subtamanho;i++) {
        soma = soma + subvetor[i];
    }

    double media;
    media = soma/(double)(subtamanho);
    media = media/nprocs;

    double media_total;
    MPI_Allreduce(&media, &media_total, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    MPI_Finalize();

    if (rank == 0) {
        printf("A média total é: %lf\n", media_total);
    }

    return 0;
}

