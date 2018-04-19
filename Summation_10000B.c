/* Tellon Smith */
/* MPI version of computing the summation of all the first consecutive 10000
   numbers(starting at 1). Restrictions are: the program must only run with 
   100 processes and MPI_Send and MPI_Recv CANNOT be used. */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

const int SIZE = 10000; //amount of numbers used for the summation

int main(int argc, char** argv)
{
	int comm_sz; //number of processes
	int my_rank; //process rank/process id
	int numbers_per_proc; //numbers per process
	int local_sum = 0; //local sum in each process
	int total_sum = 0; //total sum
	int i; //loop control variable
	int numArray[SIZE]; //array for numbers (ints)
	
	MPI_Init(NULL, NULL); //initialize MPI process	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //get number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //get process rank/process id	
	numbers_per_proc = SIZE / comm_sz; //compute amount of numbers per process
	
	int localArray[numbers_per_proc]; //array to receive numbers	
	int summation[comm_sz]; //summation of numbers from different processes
	
	//ensures that only 100 processes is used
	if (comm_sz != 100)
	{
		printf("error! the number of processes used must be 100!\n");
		MPI_Abort(MPI_COMM_WORLD, 1); //terminate the MPI process
	}//end if
	else
	{	
		//fill array with numbers
		for (i = 0; i < SIZE; i++)
		{
			numArray[i] = (i + 1); 
		}
	
		//send numbers to other processes
		MPI_Scatter(numArray, numbers_per_proc, MPI_INT, localArray, numbers_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
			
		//compute local sums
		for (i = 0; i < comm_sz; i++)
		{
			local_sum += localArray[i];
		}				
			
		//gather local sums
		MPI_Gather(&local_sum, 1, MPI_INT, summation, 1, MPI_INT, 0, MPI_COMM_WORLD);
			
		//calculate total sum
		if(my_rank == 0)
		{
			for (i = 0; i < comm_sz; i++)
			{
				total_sum += summation[i];
			}
				
			//print total sum
			printf ("The summation of all numbers is: %d\n", total_sum);
			
			//print local sums received
			for (i = 0; i < comm_sz; i++)
			{
				printf("The local sum computed by P%d is: %d\n",i,summation[i]);
			}
		}
	}//end else
		
	MPI_Finalize(); //finalize MPI process
}