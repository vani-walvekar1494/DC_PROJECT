#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Define total matrix dimensions
const int TOTAL_ROWS = 300;  // Fixed total number of rows
const int COLS = 300;        // Fixed total number of columns

void initialize_boundaries(std::vector<double>& matrix, int rows, int cols) {
    if (matrix.size() != rows * cols) {
        matrix.resize(rows * cols, 0.0);
    }
    // Initializing boundaries conditionally based on global matrix position
}

void update_laplace(std::vector<double>& matrix, std::vector<double>& new_matrix, int rows, int cols) {
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            new_matrix[i * cols + j] = 0.25 * (matrix[(i - 1) * cols + j] +
                                               matrix[(i + 1) * cols + j] +
                                               matrix[i * cols + (j - 1)] +
                                               matrix[i * cols + (j + 1)]);
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_proc = TOTAL_ROWS / size + 2; // Calculate rows per process, add ghost rows
    std::vector<double> matrix(rows_per_proc * COLS), new_matrix(rows_per_proc * COLS);

    initialize_boundaries(matrix, rows_per_proc, COLS);
    double start_time = MPI_Wtime();

    for (int iter = 0; iter < 1000; ++iter) {
        update_laplace(matrix, new_matrix, rows_per_proc, COLS);
        matrix.swap(new_matrix);  // Swap matrices for the next iteration
    }

    double end_time = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Total time: " << (end_time - start_time) << " seconds\n";
    }

    MPI_Finalize();
    return 0;
}
