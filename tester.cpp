#include <iostream>
#include <mpi.h>
#include <string>


// Constants: size of matrix and amount of threads
const int maxn = 12;
const int num_workers = 4;


int main(int argc, char* argv[]) {

    // Local variables
    int my_rank;
    int size;

    // Init mpi, get rank of worker, get total num workers
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_worker = maxn / size;
    int upper_neighbor;
    int lower_neighbor;

    // Allocate ghost points to xlocal
    double xlocal[rows_per_worker + 2][maxn];

    // Init local data with worker rank
    for (int i=0; i<=rows_per_worker+1; i++){
        for (int j=0; j<maxn; j++){
            if (i==0 || i==rows_per_worker+1){
                xlocal[i][j] = -1.0;
            } else {
                xlocal[i][j] = my_rank;
            }
	}
    }

    // get neighbors
    upper_neighbor = my_rank + 1;
    lower_neighbor = my_rank - 1;
    
    // Exchange ghost point data with upper neighbor's boottom row
    if (my_rank < size-1){
        MPI_Send(xlocal[rows_per_worker], maxn, MPI_DOUBLE, upper_neighbor, 0, MPI_COMM_WORLD);
        MPI_Recv(xlocal[rows_per_worker+1], maxn, MPI_DOUBLE, upper_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    // Exchange ghost point data with lower neighbor's top row
    if (my_rank > 0){
        MPI_Send(xlocal[1], maxn, MPI_DOUBLE, lower_neighbor, 0, MPI_COMM_WORLD);
        MPI_Recv(xlocal[0], maxn, MPI_DOUBLE, lower_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    // Test Routine:
    std::cout << "\nWorker " << my_rank << " ghost point vals:" << std::endl;
    if (my_rank > 0) {
        std::cout << "\tUpper Ghost Row (from worker " << lower_neighbor << "):" << std::endl;
	std::cout << "\t\t";
	for (int j=0; j<maxn; j++){
            std::cout << xlocal[0][j] << " ";
        }
        std::cout<<" "<<std::endl;
    }

    if (my_rank < size-1) {
        std::cout << "\t Lower Ghost Row (from worker " << upper_neighbor << "):" << std::endl;
	std::cout << "\t\t";
	for (int j=0; j<maxn; j++){
            std::cout << xlocal[rows_per_worker+1][j] << " ";
        }
        std::cout<<" "<<std::endl;
    }

    // Matrix Output: Disabled due to misprints from process execution timing
    /*
    std::cout << "Total Matrix for Worker " << my_rank << ": " << std::endl;
    for (int i=0; i<rows_per_worker+2; i++){
    	for (int j=0; j<maxn; j++){
	    std::cout <<xlocal[i][j] << " ";
	}
	std::cout<<" "<<std::endl;
    }
    */

    MPI_Finalize();

    return 0;
}
