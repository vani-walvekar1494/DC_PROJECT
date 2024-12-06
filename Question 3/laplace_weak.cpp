#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Define matrix dimensions per process
const int ROWS_PER_PROC = 100;  // Adjust as needed for workload per process
const int COLS = 300;           // Adjust as needed

void initialize_boundaries(std::vector<double>& matrix, int rows, int cols) {
    if (matrix.size() != rows * cols) {
        matrix.resize(rows * cols, 0.0);
    }
    // Initialize first and last column
    for (int i = 0; i < rows; ++i) {
        matrix[i * cols] = rand() % 100 / 10.0;      // First column
        matrix[i * cols + cols - 1] = rand() % 100 / 10.0; // Last column
    }
    // Initialize first and last row
    for (int j = 0; j < cols; ++j) {
        matrix[j] = rand() % 100 / 10.0; // First row
        matrix[(rows - 1) * cols + j] = rand() % 100 / 10.0; // Last row
    }
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

    int rows = ROWS_PER_PROC + 2; // Adding ghost rows
    std::vector<double> matrix(rows * COLS), new_matrix(rows * COLS);

    initialize_boundaries(matrix, rows, COLS);
    double start_time = MPI_Wtime();

    for (int iter = 0; iter < 1000; ++iter) {
        update_laplace(matrix, new_matrix, rows, COLS);
        matrix.swap(new_matrix);  // Swap matrices for the next iteration
    }

    double end_time = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Total time: " << (end_time - start_time) << " seconds\n";
    }

    MPI_Finalize();
    return 0;
}
