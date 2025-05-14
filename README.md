# Parallel Data Structure for Stencil Applications

This program implements a parallel data structure optimized for stencil applications. A stencil application calculates values in a 2D array, where each element's new value depends on its neighbors (north, east, south, west). This data structure efficiently manages data distribution and boundary communication between processing units (workers) using MPI.

## Data Structure Description

The core of the data structure is a 2D array divided into slabs (contiguous rows), with each slab assigned to a different worker. For a global array `x[maxn][maxn]`, each worker holds a local array `xlocal[maxn][maxn/size]`, where `size` is the number of workers.

To facilitate stencil computations, each worker's local array includes "ghost points." These ghost points store the boundary values from neighboring workers, enabling access to the required adjacent data.

**Key components:**

* **Local Array:** The portion of the main data array assigned to a worker.
* **Ghost Points:** Extra rows/columns at the edges of the local array that hold data from neighboring workers.
* **Slabs:** Contiguous rows of the 2D array.

## Implementation Details

The code divides the global array `x` into equally sized slabs and copies the adjacent edge values to the neighboring workers.

**Key Features:**

* Array division into equal-sized strips.
* Exchange of adjacent edge data between neighboring workers.
* Use of ghost points to store off-worker data.
* Non-periodic boundary handling.

**Communication:**

* `MPI_Send` and `MPI_Recv` are used for communication between workers.

**Testing:**

The `tester.cpp` file includes test code that:

1.  Initializes each worker's local section of the array with its worker rank.
2.  Initializes each worker's ghost points with -1.
3.  Exchanges data with neighboring workers.
4.  Verifies that the ghost points contain the correct values from the neighboring workers.
5.  Prints the values of each worker's ghost rows.

**Example:**

For `maxn = 12` and `size = 4`, each worker's `xlocal` is 12x3. Worker 0 has ghost points for the data from worker 1. Worker 3 has ghost points for the data from worker 2.

## Repository Contents

The repository contains the following files:

* `README.md`: This file.
* `tester.cpp`: Contains the main function, test code, and program entry point.
* `Makefile`: A `Makefile` for compiling the code.
* `run.sh`: A bash script for running the program on a Linux-based scheduler (e.g., SLURM).

## Makefile Usage

The repository includes a `Makefile` to simplify the build process.

**Targets:**

* `all`: Compiles the code and creates the executable.
* `clean`: Removes all compiled files (object files and executable).
* `run`: Runs the executable. You will need to specify the number of processes (workers) using `mpiexec`.

**Example Usage:**

1.  **Compile:**

    ```bash
    make all
    ```

2.  **Clean:**

    ```bash
    make clean
    ```

3.  **Run (with 4 processes):**

    ```bash
    mpiexec -n 4 ./your_executable_name
    ```

    (Replace `your_executable_name` with the actual name of your executable.)

## `run.sh` Usage

The repository also includes a `run.sh` script for running the program on a Linux-based scheduler, such as SLURM. This script simplifies the process of submitting your job to the cluster.

**To use the script:**

1.  Ensure that the script is executable:

    ```bash
    chmod +x run.sh
    ```

2.  Modify the script to match your cluster's specific configuration:

    * Specify the number of nodes/cores using the `#SBATCH -n` or `#SBATCH --nodes` directives.
    * Set the job name with the `#SBATCH -J` directive.
    * Define the output file using the `#SBATCH -o` directive.
    * Specify the partition (if required) by uncommenting and editing the `#SBATCH -p` directive.
    * Set any other necessary SLURM options.

3.  Submit the job to the scheduler:

    ```bash
    sbatch run.sh
    ```

## Prerequisites

* An MPI installation (e.g., OpenMPI, MPICH).
* A C compiler (e.g., gcc, clang).
* A Linux-based system (for using the `run.sh` script with a scheduler).

## Compilation

To compile the code, run the following command in the repository's root directory:

```bash
make all
This will compile the source files and create an executable.Running the CodeTo run the compiled executable, use the following command:mpiexec -n <number_of_processes> ./tester
Replace <number_of_processes> with the number of MPI processes you want to use
