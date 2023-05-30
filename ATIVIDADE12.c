#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define ARRAY_SIZE 100

double calcular_media_local(double* array, int local_size) {
    double soma = 0.0;
    for (int i = 0; i < local_size; i++) {
        soma += array[i];
    }
    return soma / local_size;
}

double calcular_desvio_padrao_local(double* array, int local_size, double media_local) {
    double soma_quadrados_diferencas = 0.0;
    for (int i = 0; i < local_size; i++) {
        double diferenca = array[i] - media_local;
        soma_quadrados_diferencas += diferenca * diferenca;
    }
    return sqrt(soma_quadrados_diferencas / local_size);
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double* array = NULL;
    int local_size = ARRAY_SIZE / world_size;
    double* local_array = (double*)malloc(local_size * sizeof(double));

    if (world_rank == 0) {
      array = (double*)malloc(ARRAY_SIZE * sizeof(double));
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = i + 1;
        }
    }

    MPI_Scatter(array, local_size, MPI_DOUBLE, local_array, local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double media_local = calcular_media_local(local_array, local_size);

    double desvio_padrao_local = calcular_desvio_padrao_local(local_array, local_size, media_local);

    double soma_quadrados_diferencas_global = 0.0;
    MPI_Reduce(&desvio_padrao_local, &soma_quadrados_diferencas_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        double media_global = media_local;
        MPI_Reduce(MPI_IN_PLACE, &media_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        media_global /= ARRAY_SIZE;

        double desvio_padrao_global = sqrt(soma_quadrados_diferencas_global / ARRAY_SIZE);

        printf("Desvio padrão global

