//assumes equal rows and columns in both matrix a and b
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int SIZE = 640; //number of rows and columns

//fills the matrix with the specified number
void fillMatrix(int matrix[][SIZE], int num);

void multiplyMatrix(int matrixA[][SIZE], int matrixB[][SIZE], int matrixC[][SIZE]);

void printMatrix(FILE *file, int matrix[][SIZE]);


int main()
{
	double time_spent;
	clock_t begin = clock();
	FILE * file;
	file = fopen("TeamNameserialOutput.txt", "w");

	int matrixA[SIZE][SIZE]; //first matrix
	int matrixB[SIZE][SIZE]; //second matrix
	int matrixC[SIZE][SIZE]; //results matrix

	fillMatrix(matrixA, 1); //fill matrixA with 1's
	fillMatrix(matrixB, 2); //fill matrixB with 2's
	fillMatrix(matrixC, 0); //fill matrixC with 0's (initialize)

	multiplyMatrix(matrixA, matrixB, matrixC);

	printMatrix(file, matrixC);

	clock_t end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	fprintf(file, "\ntime taken to perform matrix multiplication is: %f\n",time_spent);

	fclose(file);
	return 0;
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
