#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

using namespace std;

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

    srand(time(nullptr) + world_rank);
    vector<unsigned long long> iterations_options = {10000000, 50000000, 100000000, 500000000};

    const int MASTER = 0;
    int num_simulations = 100;
    double start_time, end_time;

    if (world_rank == MASTER) {
        start_time = MPI_Wtime();
        int num_workers = world_size - 1;
        int simulations_per_worker = num_simulations / num_workers;
        int extra = num_simulations % num_workers;

        // Send tasks to each worker
        for (int i = 1; i <= num_workers; ++i) {
            int count = simulations_per_worker + (i <= extra ? 1 : 0);
            MPI_Send(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // Gather results from workers
        double total_pi = 0.0;
        int total_count = 0;
        for (int i = 1; i <= num_workers; ++i) {
            double pi_sum;
            int count;
            MPI_Recv(&pi_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_pi += pi_sum;
            total_count += count;
        }
        double average_pi = total_pi / total_count;
        end_time = MPI_Wtime();

        cout << "Average Pi = " << average_pi << endl;
        cout << "Total elapsed time: " << (end_time - start_time) << " seconds" << endl;
    } else {
        int count;
        MPI_Recv(&count, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double pi_sum = 0.0;
        for (int i = 0; i < count; ++i) {
            int idx = rand() % iterations_options.size();
            unsigned long long num_iterations = iterations_options[idx];
            double pi = calculatePi(num_iterations);
            pi_sum += pi;
        }
        MPI_Send(&pi_sum, 1, MPI_DOUBLE, MASTER, 0, MPI_COMM_WORLD);
        MPI_Send(&count, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
