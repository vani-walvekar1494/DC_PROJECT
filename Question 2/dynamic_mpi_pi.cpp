#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

#define MASTER 0
#define TASK_REQUEST 1
#define TASK_FINISH 2
#define SHUTDOWN 3

// Function to calculate Pi using the Monte Carlo method
double calculatePi(unsigned long long num_iterations) {
    unsigned long long inside_circle = 0;
    for (unsigned long long i = 0; i < num_iterations; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }
    return (4.0 * inside_circle) / num_iterations;
}

int main(int argc, char** argv) {
    int world_rank, world_size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    srand(time(nullptr) + world_rank);  // Seed random number generator with different values based on rank
    std::vector<unsigned long long> iterations_options = {10000000, 50000000, 100000000, 500000000};
    double start_time, end_time;

    if (world_rank == MASTER) {
        start_time = MPI_Wtime();
        int total_tasks = 100;
        int task_count = 0;
        double total_pi = 0;
        int total_completed = 0;
        MPI_Status status;

        // Send tasks to all workers
        while (task_count < total_tasks) {
            // Find a worker that is requesting a task
            int worker_rank;
            MPI_Recv(&worker_rank, 1, MPI_INT, MPI_ANY_SOURCE, TASK_REQUEST, MPI_COMM_WORLD, &status);
            
            // Send a task to the worker
            int idx = rand() % iterations_options.size();
            unsigned long long num_iterations = iterations_options[idx];
            MPI_Send(&num_iterations, 1, MPI_UNSIGNED_LONG_LONG, status.MPI_SOURCE, TASK_FINISH, MPI_COMM_WORLD);
            task_count++;
        }

        // Send shutdown signal to all workers
        for (int i = 1; i < world_size; i++) {
            unsigned long long shutdown = 0;
            MPI_Send(&shutdown, 1, MPI_UNSIGNED_LONG_LONG, i, SHUTDOWN, MPI_COMM_WORLD);
        }

        // Collect results from all workers
        for (int i = 1; i < world_size; i++) {
            double pi;
            MPI_Recv(&pi, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            total_pi += pi;
            total_completed++;
        }

        end_time = MPI_Wtime();

        std::cout << "Average Pi = " << (total_pi / total_completed) << std::endl;
        std::cout << "Total time taken = " << (end_time - start_time) << " seconds" << std::endl;

    } else {
        bool running = true;
        while (running) {
            // Request a new task
            MPI_Send(&world_rank, 1, MPI_INT, MASTER, TASK_REQUEST, MPI_COMM_WORLD);

            // Receive a task or shutdown command
            unsigned long long num_iterations;
            MPI_Status status;
            MPI_Recv(&num_iterations, 1, MPI_UNSIGNED_LONG_LONG, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == SHUTDOWN) {
                running = false;
            } else {
                // Calculate Pi for the received number of iterations
                double pi = calculatePi(num_iterations);
                MPI_Send(&pi, 1, MPI_DOUBLE, MASTER, TASK_FINISH, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
