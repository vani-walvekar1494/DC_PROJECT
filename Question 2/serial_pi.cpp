#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Function to calculate Pi using Monte Carlo method
double calculatePi(unsigned long long num_iterations) {
    unsigned long long inside_circle = 0;
    double x, y, pi;

    for (unsigned long long i = 0; i < num_iterations; ++i) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) {
            inside_circle++;
        }
    }

    pi = (double)inside_circle / num_iterations * 4;
    return pi;
}

int main() {
    srand(time(NULL));  // Initialize random seed based on current time

    // Array of different number of iterations to use
    unsigned long long iterations[] = {10000000, 50000000, 100000000, 500000000};
    int num_runs = 3;  // Number of times to run the simulation

    for (int i = 0; i < num_runs; ++i) {
        // Randomly select number of iterations
        int idx = rand() % 4;
        unsigned long long num_iterations = iterations[idx];

        // Start timer
        clock_t start = clock();

        // Calculate Pi
        double pi = calculatePi(num_iterations);

        // Stop timer and calculate elapsed time
        clock_t end = clock();
        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;

        // Print results
        std::cout << "Run " << (i + 1) << ":" << std::endl;
        std::cout << "Number of iterations: " << num_iterations << std::endl;
        std::cout << "Calculated Pi: " << pi << std::endl;
        std::cout << "Elapsed time: " << elapsed_time << " seconds" << std::endl << std::endl;
    }

    return 0;
}
