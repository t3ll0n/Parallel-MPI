//assumes equal rows and columns in both matrix a and b
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

const int SIZE = 640; //number of rows and columns

//fills the matrix with the specified number
void fillMatrix(int matrix[][SIZE], int num);

void multiplyMatrix(int matrixA[][SIZE], int matrixB[][SIZE], int matrixC[][SIZE]);

void printMatrix(FILE *file, int matrix[][SIZE]);


int main(int argc, char** argv)
{
	int comm_sz; //number of processes
	int my_rank; //process rank/process id
	int start;
	int end;
	int i,j,k;//k?
	
	clock_t begin = clock();
	FILE * file;
	file = fopen("TeamNameserialOutput.txt", "w"); //??
	int matrixA[SIZE][SIZE]; //first matrix //??
	int matrixB[SIZE][SIZE]; //second matrix
	int matrixC[SIZE][SIZE]; //results matrix
	
	MPI_Init(NULL, NULL); //initialize MPI process	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //get number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //get process rank/process id	
	//numbers_per_proc = SIZE / comm_sz; //compute amount of numbers per process
	
	//ensures that only 16 processes is used
	if (comm_sz != 16)
	{
		printf("error! the number of processes used must be 100!\n");
		MPI_Abort(MPI_COMM_WORLD, 1); //terminate the MPI process
		exit(-1);
	}//end if
	else
	{
		start = ((my_rank * SIZE) / comm_sz);
		end = ((my_rank + 1) * (SIZE/comm_sz));
	
	//if process zero (p0)
		if (my_rank == 0)	
		{	
			fillMatrix(matrixA, 1); //fill matrixA with 1's
			fillMatrix(matrixB, 2); //fill matrixB with 2's
			fillMatrix(matrixC, 0); //fill matrixC with 0's (initialize)
		}
		
		MPI_Bcast(matrixB,(SIZE*SIZE),MPI_INT,0,MPI_COMM_WORLD);
		MPI_Scatter(&matrixA[0][0],(SIZE*SIZE/comm_sz),MPI_INT,&matrixA[start][0],(SIZE*SIZE/comm_sz),MPI_INT,0,MPI_COMM_WORLD);
		
		//printf("computing slice %d (from row %d to %d)\n", myrank, from, to-1);
		for (i = start; i < end; i++)
		{			
			for (j = 0; j < SIZE; j++)
			{
				matrixC[i][j]=0; //?needed?
				for (k = 0; k < SIZE; k++)
				{
					matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
				}
			}
		}
		MPI_Gather (matrixC[start], (SIZE*SIZE/comm_sz), MPI_INT, matrixC, (SIZE*SIZE/comm_sz), MPI_INT, 0, MPI_COMM_WORLD);
		
	//multiplyMatrix(matrixA, matrixB, matrixC);

	printMatrix(file, matrixC);

	//clock_t end = clock();
	//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	//fprintf(file, "\ntime taken to perform matrix multiplication is: %f\n",time_spent);

	fclose(file);
	MPI_Finalize();
	}
}


void fillMatrix(int matrix[][SIZE], int num)
{
	int i,j; //loop control variables

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			matrix[i][j] = num;
		}
	}
}

void multiplyMatrix(int matrixA[][SIZE], int matrixB[][SIZE], int matrixC[][SIZE])
{
	int i,j,k; //loop control variables

	for(i = 0; i < SIZE; ++i)
	{
		for(j = 0; j < SIZE; ++j)
		{
            for(k = 0; k < SIZE; ++k)
            {
                matrixC[i][j]+=matrixA[i][k]*matrixB[k][j];
            }//end 3rd loop
		}//end 2nd loop
	}//end 1st loop
}

void printMatrix(FILE *file, int matrix[][SIZE])
{
	int i,j; //loop control variables

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fprintf(file, "%d ",matrix[i][j]);
		}
		fprintf(file, "\n");
	}
}
