# Parallel Data Structure for Stencil Applications

This assignment involves implementing a parallel data structure optimized for stencil applications. A stencil application calculates values in a 2D array, where each element's new value depends on its neighbors (north, east, south, west). This data structure efficiently manages data distribution and boundary communication between processing units (workers).

## Data Structure Description

The core of the data structure is a 2D array divided into slabs (contiguous rows), with each slab assigned to a different worker. For a global array `x[maxn][maxn]`, each worker holds a local array `xlocal[maxn][maxn/size]`, where `size` is the number of workers.

To facilitate stencil computations, each worker's local array includes "ghost points." These ghost points store the boundary values from neighboring workers, enabling access to the required adjacent data.

**Key components:**

* **Local Array:** The portion of the main data array assigned to a worker.
* **Ghost Points:** Extra rows/columns at the edges of the local array that hold data from neighboring workers.
* **Slabs:** Contiguous rows of the 2D array.

## Implementation Details

You are to write code that divides the global array `x` into equally sized slabs and copies the adjacent edge values to the neighboring workers.

**Assumptions:**

* The global array is square (`maxn` x `maxn`).
* `maxn` is evenly divisible by the number of workers.
* The number of workers is fixed (or minimum).
* Non-periodic boundaries:
    * The top worker (rank = size - 1) communicates only with the worker below it (rank = size - 2).
    * The bottom worker (rank = 0) communicates only with the worker above it (rank = size - 1).

**Communication:**

* Use `MPI_Send` and `MPI_Recv` for communication between workers.

**Testing:**

1.  Each worker fills its local section of the array with its worker rank.
2.  Each worker fills its ghost points with -1.
3.  After the data exchange, verify that the ghost points contain the correct values from the neighboring workers.
4.  Print the values of each worker's ghost rows.

**Example:**

For `maxn = 12` and `size = 4`, each worker's `xlocal` will be 12x3. Worker 0 will have ghost points for the data from worker 1. Worker 3 will have ghost points for the data from worker 2.

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

## run.sh Usage

The directory also contains a `run.sh` script for running the tester on a Linux-based scheduler, such as SLURM. This script simplifies the process of submitting your job to the cluster.

**To use the script:**

1.  Ensure that the script is executable:

    ```bash
    chmod +x run.sh
    ```

2.  Modify the script to match your cluster's specific configuration:
    * **Specify the number of nodes/cores:** Adjust the `#SBATCH -n` or `#SBATCH --nodes` directives.
    * **Set the job name:** Modify the `#SBATCH -J` directive.
    * **Define the output file:** Change the `#SBATCH -o` directive.
    * **Specify the partition (if required):** Uncomment and edit the `#SBATCH -p` directive.
    * **Set any other necessary SLURM options.**

3.  Submit the job to the scheduler:

    ```bash
    sbatch run.sh
    ```

## Directory Structure


parallel_data_structure/
|-- README.md
|-- src/
|   |-- data_structure.c       (Contains the data structure implementation)
|   |-- data_structure.h       (Contains the data structure header file)
|   |-- main.c                (Contains the main function and test code)
|-- Makefile
|-- run.sh                  (SLURM job submission script)


## Important Considerations

* Ensure your MPI environment is set up correctly.
* The `Makefile` assumes a standard MPI installation (e.g., OpenMPI, MPICH). You may need to adjust compiler flags or library paths if your setup is different.
* This implementation uses blocking `MPI_Send` and `MPI_Recv`. For very large arrays, you might consider non-blocking communication for better performance.
* Error handling (checking the return values of MPI functions) is crucial for robust code.
* The `run.sh` script is a template and will likely require modifications to work correctly on your specific cluster.  Consult your cluster's documentation for details on SLURM parameters.

