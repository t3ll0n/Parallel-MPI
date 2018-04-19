/* Tellon Smith */
/* MPI version of computing the summation of all the first consecutive 10000
   numbers(starting at 1). Restrictions are: the program must only run with 
   100 processes and only MPI_Send and MPI_Recv can be used. */

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
	int i; //loop control variable
	
	MPI_Init(NULL, NULL); //initialize MPI process	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //get number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //get process rank/process id	
	numbers_per_proc = SIZE / comm_sz; //compute amount of numbers per process
	
	//ensures that only 100 processes is used
	if (comm_sz != 100)
	{
		printf("error! the number of processes used must be 100!\n");
		MPI_Abort(MPI_COMM_WORLD, 1); //terminate the MPI process
	}//end if
	else
	{	
		//if process zero (p0)
		if (my_rank == 0)
		{
			int total_sum = 0; //total sum
			int recv_sum = 0; //sum received by other processes
			int numArray[SIZE]; //array for numbers (ints)
			int summation[comm_sz]; //summation of numbers from different processes			
			
			//fill array with numbers
			for (i = 0; i < SIZE; i++)
			{
				numArray[i] = (i + 1); 
			}
		
			//calculate local sum for p0
			for (i = 0; i < numbers_per_proc; i++)
			{
				local_sum += numArray[i];
			}
			
			//send p0's local_sum to summation array
			summation[0] = local_sum;
			
			//send numbers to other processes
			for (i = 1; i < comm_sz; i++)
			{
				MPI_Send(numArray+(numbers_per_proc*i), numbers_per_proc, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
			
			//receive sums from other processes and add to summation array
			for (i = 1; i < comm_sz; i++)
			{
				MPI_Recv(&recv_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				summation[i] = recv_sum;
			}
			
			//calculate summation
			for (i = 0; i < comm_sz; i++)
			{
				total_sum += summation[i];
			}
			
			//print total sum
			printf ("The summation of all numbers is: %d\n", total_sum);
			
			//print local sums from each process
			for (i = 0; i < comm_sz; i++)
			{
				printf("The local sum computed by P%d is: %d\n",i,summation[i]);
			}
		}//end if
		
		//if rank != 0
		else
		{
			
			int localArray[numbers_per_proc]; //array to receive numbers
			
			//receive numbers from p0
			MPI_Recv(&localArray, numbers_per_proc, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			//compute sum for numbers received
			for (i = 0; i < numbers_per_proc; i++)
			{
				local_sum += localArray[i];	
			}
			
			//send local sum back to p0
			MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}//end else
	}//end else
		
	MPI_Finalize(); //finalize MPI process
}