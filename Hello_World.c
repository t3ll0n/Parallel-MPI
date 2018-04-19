//hello world using mpi

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	//initialize the MPI environment
	MPI_Init(&argc, &argv);
	
	//get the number of processes
	int num_processes;
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	
	//Get the rank of the process
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	//print "hello world message" from respective processes
	printf("Hello world from process %d of %d \n", my_rank, num_processes);
	
	//finalize the MPI environment
	MPI_Finalize();
	return 0;
}