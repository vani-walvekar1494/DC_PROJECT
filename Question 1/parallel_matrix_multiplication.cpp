#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Matrix dimension
    const int n = 32; // Change to 256 for the second run
    int rows_per_proc = n / size;

    // Local matrices
    std::vector<double> A_local(rows_per_proc * n, 1); // Initialize to 1
    std::vector<double> B(n * n, 1);                  // Initialize to 1
    std::vector<double> C_local(rows_per_proc * n, 0);

    // Broadcast matrix B
    MPI_Bcast(B.data(), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Start timing
    double start_time = MPI_Wtime();

    // Perform matrix multiplication
    for (int i = 0; i < rows_per_proc; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C_local[i * n + j] += A_local[i * n + k] * B[k * n + j];
            }
        }
    }

    // Gather results at root
    std::vector<double> C;
    if (rank == 0) {
        C.resize(n * n);
    }
    MPI_Gather(C_local.data(), rows_per_proc * n, MPI_DOUBLE, C.data(), rows_per_proc * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // End timing
    double end_time = MPI_Wtime();

    if (rank == 0) {
        std::cout << "Execution time for n = " << n << " with p = " << size
                  << ": " << (end_time - start_time) << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
