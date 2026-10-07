#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size;
    long long niter = 10000000; // 10,000,000 times as requested
    long long local_count = 0;
    long long global_count = 0;
    double x, y, z, pi;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Start timer on rank 0
    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    // Seed the random number generator uniquely for each process
    srand((unsigned int)(time(NULL) + rank * 1000));

    // Calculate how many iterations this specific process needs to do
    long long local_niter = niter / size;

    // Monte Carlo simulation
    for (long long i = 0; i < local_niter; ++i) {
        // Generate random numbers between 0 and 1
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;
        
        // If the point is inside the unit circle, increment count
        if (z <= 1) {
            local_count++;
        }
    }

    // Combine all the local counts into the global count on processor 0
    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Rank 0 calculates Pi and prints the result
    if (rank == 0) {
        end_time = MPI_Wtime();
        
        // We use the actual total iterations done (size * local_niter)
        long long total_niter = local_niter * size;
        pi = ((double)global_count / total_niter) * 4.0;
        
        printf("Calculated Pi: %f\n", pi);
        printf("Time taken: %f seconds with %d processors\n", end_time - start_time, size);
    }

    MPI_Finalize();
    return 0;
}
