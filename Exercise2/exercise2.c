#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    long long N = 10000000;
    long long local_sum = 0;
    long long global_sum = 0;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Start timer on rank 0
    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    // Calculate the start and end of the range for this specific process
    long long chunk_size = N / size;
    long long start = rank * chunk_size + 1;
    long long end = (rank == size - 1) ? N : start + chunk_size - 1;

    // Calculate the local sum for this process's chunk
    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    // Combine all local sums into the global_sum on rank 0
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Stop timer and print result
    if (rank == 0) {
        end_time = MPI_Wtime();
        printf("Total Sum: %lld\n", global_sum);
        printf("Time taken: %f seconds with %d processors\n", end_time - start_time, size);
    }

    MPI_Finalize();
    return 0;
}
