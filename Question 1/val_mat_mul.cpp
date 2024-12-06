#include <iostream>
#include <fstream>
#include <mpi.h>
#include <vector>
#include <iomanip>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 8; // Matrix dimension
    const int rows_per_proc = n / size; // Rows per process

    // Check if the number of processes divides matrix size evenly
    if (n % size != 0) {
        if (rank == 0) {
            std::cerr << "Matrix size must be divisible by the number of processes." << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    std::vector<double> A_local(rows_per_proc * n), B(n * n), C_local(rows_per_proc * n, 0);

    // Initialize matrices A and B at root
    if (rank == 0) {
        std::vector<double> A(n * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i * n + j] = i * n + j;
                B[i * n + j] = i * n + j;
            }
        }
        // Scatter matrix A to all processes
        MPI_Scatter(A.data(), rows_per_proc * n, MPI_DOUBLE, A_local.data(), rows_per_proc * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatter(nullptr, 0, MPI_DOUBLE, A_local.data(), rows_per_proc * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    // Broadcast matrix B to all processes
    MPI_Bcast(B.data(), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Perform local matrix multiplication
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

    // Root process writes the result to a file
    if (rank == 0) {
        std::ofstream outfile("matrix_output.txt");
        outfile << "Matrix C (Result):" << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                outfile << std::setw(5) << C[i * n + j] << " ";
            }
            outfile << std::endl;
        }
        outfile.close();
        std::cout << "Result written to matrix_output.txt" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
