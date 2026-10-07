#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size;
    long long niter = 10000000;
    long long local_count = 0;
    long long global_count = 0;
    double x, y, z, pi;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    srand((unsigned int)(time(NULL) + rank * 1000));
    long long local_niter = niter / size;

    // Monte Carlo simulation
    for (long long i = 0; i < local_niter; ++i) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;
        if (z <= 1) {
            local_count++;
        }
    }

    if (rank != 0) {
        // EXERCISE 7: Use Buffered Send (BSend) instead of Send
        // 1. Allocate and attach a buffer
        int buffer_size = sizeof(long long) + MPI_BSEND_OVERHEAD;
        void* buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);

        // 2. Use MPI_Bsend
        MPI_Bsend(&local_count, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);

        // 3. Detach and free the buffer
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    } 
    else {
        // Processor 0 RECEIVES from ANY SOURCE
        global_count = local_count;
        long long received_count;
        MPI_Status status;

        for (int i = 1; i < size; i++) {
            MPI_Recv(&received_count, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            global_count += received_count;
            printf("Processor 0 received a buffered count from Processor %d\n", status.MPI_SOURCE);
        }

        // Final calculation
        end_time = MPI_Wtime();
        long long total_niter = local_niter * size;
        pi = ((double)global_count / total_niter) * 4.0;
        
        printf("Calculated Pi (with ANY_SOURCE and BSend): %f\n", pi);
        printf("Time taken: %f seconds with %d processors\n", end_time - start_time, size);
    }

    MPI_Finalize();
    return 0;
}
