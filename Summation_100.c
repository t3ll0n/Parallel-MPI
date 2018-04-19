/* Tellon Smith */
/* Compute the summation of 100 integer numbers */
/* Each process would have a dynamically created array 
   (with the right size) initialized with the following
   values: Array for process 0: {0,1,2,3,4,5,6,7,8,9}, 
   Array for process 1: {10,11,12,13,....etc.} */
   
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

const int SIZE = 100; //total number of elements

int main(int argc, char** argv)
{
	int comm_sz; //number of processes
	int my_rank; //process rank/process id
	int num_elements_per_proc; //elements per process
	int local_sum = 0; //local sum
	int global_sum = 0; //global sum
	int *numArray; //dynamic array for numbers (ints)
	int i; //loop control variable
	
	MPI_Init(NULL, NULL); //initialize MPI process	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //get number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //get process rank/process id
	num_elements_per_proc = SIZE / comm_sz;
	
	if (SIZE % comm_sz != 0) //if SIZE is not divisible by the number of processes 
	{
		printf("error! the size is %d and must be divisible\n"
		"by the number of processes\n", SIZE);
		MPI_Abort(MPI_COMM_WORLD, 1); //terminate the MPI process
	}
	else
	{
		numArray = calloc(num_elements_per_proc, sizeof(int));
		
		//initialize array in each process
		for (i = 0; i < num_elements_per_proc; i++)
		{
			numArray[i] = ((my_rank * num_elements_per_proc) + i);
		}
		
		//calculate local sum for each process
		for (i = 0; i < num_elements_per_proc; i++)
		{
			local_sum += numArray[i];
		}
		
		// reduce all of the local sums into the global_sum
		MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		
		// print local sum
		printf("local sum for process %d = %d\n", my_rank, local_sum);
		
		if (my_rank == 0) //print global_sum
		{
			printf("Total sum = %d\n", global_sum);
		}
	}	
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize(); //finalize MPI process
}   