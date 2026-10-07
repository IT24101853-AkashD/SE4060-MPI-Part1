#include <cstdio>
#include <cstdlib>
#include <mpi.h>

int main(void)
{
    int rank;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char name[30];
    int len;
    MPI_Get_processor_name( name, &len );
    int x, y;
    x = 30;

    if (rank == 1) {
      // INTENTIONAL MISTAKE: Sending to Rank 2 instead of Rank 3
      printf("Sending message to computer 2 from computer 1...\n");
      MPI_Ssend(&x, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
      printf("Computer 1 finished sending! (You will never see this line because of deadlock)\n");
    }
    else if (rank == 3) {
      // INTENTIONAL MISTAKE: Rank 3 is waiting for a message from 1, but 1 sent it to 2!
      printf("Computer 3 waiting for message from computer 1...\n");
      MPI_Recv(&y, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
      printf("In computer 3 the value of y is %d\n", y);
    }
    else {
      printf("Just a normal process From rank %d machine %s\n", rank, name);
    }

    MPI_Finalize();
    return 0;
}
