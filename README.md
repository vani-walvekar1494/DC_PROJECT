# Parallel Programming Assignment

## Overview
This project involves implementing and analyzing parallel matrix multiplication, Pi calculation using MPI, and Laplace's equation solver with weak and strong scaling techniques.

## Prerequisites
Ensure you have the following installed:
- MPI Compiler (`mpic++`)
- MPI Runtime Environment (`mpirun`)

## Compilation and Execution Commands

### 1. Matrix Multiplication

#### Validation Program
Compile the validation program**:
            mpic++ -o val_mat_mul val_mat_mul.cpp
Run with n=8 and p=8
            mpirun -np 8 ./val_mat_mul
            
#### Parallel Matrix Multiplication
Compile:
            mpic++ -o parallel_matrix_multiplication parallel_matrix_multiplication.cpp
Run for different matrix sizes and processor counts:
            For n=32:
            mpirun --oversubscribe -np 1 ./parallel_matrix_multiplication
            mpirun --oversubscribe -np 2 ./parallel_matrix_multiplication
            mpirun --oversubscribe -np 4 ./parallel_matrix_multiplication
            mpirun --oversubscribe -np 8 ./parallel_matrix_multiplication
            mpirun --oversubscribe -np 16 ./parallel_matrix_multiplication
            For n=256:
            mpirun -np 1 ./parallel_matrix_multiplication
            mpirun -np 2 ./parallel_matrix_multiplication
            mpirun -np 4 ./parallel_matrix_multiplication
            mpirun -np 8 ./parallel_matrix_multiplication
            mpirun -np 16 ./parallel_matrix_multiplication



#### 2. Pi Calculation

Static Memory Allocation
Compile the program:
            mpic++ -o mpi_pi_calculate mpi_pi_calculate.cpp
Run for different processor counts:
            mpirun -np 4 ./mpi_pi_calculate
            mpirun -np 8 ./mpi_pi_calculate
            mpirun -np 12 ./mpi_pi_calculate
            mpirun -np 16 ./mpi_pi_calculate
Dynamic Memory Allocation
Compile the program:
            mpic++ -o dynamic_mpi_pi dynamic_mpi_pi.cpp
Run for different processor counts:
            mpirun -np 4 ./dynamic_mpi_pi
            mpirun -np 8 ./dynamic_mpi_pi
            mpirun -np 12 ./dynamic_mpi_pi
            mpirun -np 16 ./dynamic_mpi_pi


##### 3. Laplace Equation Solver
Weak Scaling
Compile:
            mpic++ -o laplace_weak laplace_weak.cpp
Run for various processor counts:
            mpirun -np 1 ./laplace_weak
            mpirun -np 2 ./laplace_weak
            mpirun -np 4 ./laplace_weak
            mpirun -np 6 ./laplace_weak
            mpirun -np 8 ./laplace_weak
            mpirun -np 10 ./laplace_weak
Strong Scaling
Compile:
            mpic++ -o laplace_strong laplace_strong.cpp
Run for various processor counts:
            mpirun -np 1 ./laplace_strong
            mpirun -np 2 ./laplace_strong
            mpirun -np 4 ./laplace_strong
            mpirun -np 6 ./laplace_strong
            mpirun -np 8 ./laplace_strong
            mpirun -np 10 ./laplace_strong


#### Notes
Use --oversubscribe only when the number of processors exceeds physical cores.
Ensure all required files (e.g., val_mat_mul.cpp, parallel_matrix_multiplication.cpp, etc.) are in the same directory as the execution scripts.


##### Conclusion
This README provides all the commands needed to compile and execute programs across various configurations. Run these commands to explore the scalability and performance of parallel computing techniques.
