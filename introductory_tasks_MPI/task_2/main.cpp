#include <cstdlib>
#include <iostream>
#include "mpi.h"

int main(int argc, char **argv) {
   int N = atoi(argv[1]);
   int rank, size;
   int n, ibeg, iend;
   long double ans = 0;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   n = (N - 1) / size + 1;
   ibeg = rank * n + 1;
   iend = (rank + 1) * n;
   for (int i = ibeg; i <= ((iend > N) ? N : iend); ++i) {
      ans += 1.0 / i;
   }
   std::cout << "Process: " << rank << " Sum: " << ans << '\n';
   if (rank != 0) {
      MPI_Send(&ans, 1, MPI_LONG_DOUBLE, 0, 1, MPI_COMM_WORLD);
   }
   else {
      MPI_Status status;
      long double buf;
      
      for (int i = 0; i < size - 1; ++i) {
         MPI_Recv(&buf, 1, MPI_LONG_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         ans += buf;
      }
      std::cout << "The sum of " << N << " numbers is equal to: " << ans << '\n';
   }

   MPI_Finalize();
}
