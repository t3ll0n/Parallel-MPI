//Name: MPUS
//Assignment: Project Bruteforce
//Date: 03/28/17
//Purpose: demonstrate how to bruteforce a password in parallel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#define MAXCHAR 10 //for simplicity, limit pasword character count to 10, time increases exponentially with additional characters

char pwd[MAXCHAR] = "trystan"; //password user enters
int *params; //array which holds the ascii representations of starting and ending points for each process
int pwdCheck(char *password); //compare test hash to read-in hash //rename to compare string
void match_found(char *password); //print out test string and exit

/* Generates a-z, 0-9 for a, aa, aaa, aaaa, ...
 * a for serial, b divides workload
 */
void chars1(char *pwdtest, int index);
void chars2a(char *pwdtest, int index);
void chars2b(char *pwdtest, int index);
void chars3a(char *pwdtest, int index);
void chars3b(char *pwdtest, int index);
void chars4a(char *pwdtest, int index);
void chars4b(char *pwdtest, int index);
void chars5a(char *pwdtest, int index);
void chars5b(char *pwdtest, int index);
void chars6a(char *pwdtest, int index);
void chars6b(char *pwdtest, int index);
void chars7a(char *pwdtest, int index);
void chars7b(char *pwdtest, int index);
void chars8a(char *pwdtest, int index);
void chars8b(char *pwdtest, int index);
void chars9a(char *pwdtest, int index);
void chars9b(char *pwdtest, int index);
void chars10b(char *pwdtest, int index);

//timing variables
double start = 0;
double end = 0;

int main(int argc, char *argv[])
{
	int num_proc, my_rank;
	char *pwdtest;
	pwdtest = (char *)malloc((MAXCHAR+1)*sizeof(char));
	params = (int *)malloc(3*sizeof(int));
	
	MPI_Init(&argc, &argv); //start MPI
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc); //get number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //get my rank (process number)
	
	//only a-z and 0-9 are used??
	
	//0-9
	params[0] = 48 + ((10 * my_rank)/num_proc);
	params[1] = 48 + ((10 * (my_rank+1))/num_proc);
	
	//a-z
	params[2] = 97 + ((26 * my_rank)/num_proc);
	params[3] = 97 + ((26 * (my_rank+1))/num_proc);
	
	
	//start timing
	start = MPI_Wtime();
	
	//if process 0
	if(my_rank == 0)
	{
		chars1(pwdtest, 0); //run all possible commbinations for a 1 character password 
	}	
	
	chars2b(pwdtest, 0); //run all possible commbinations for a 2 character password
	chars3b(pwdtest, 0); //run all possible commbinations for a 3 character password
	chars4b(pwdtest, 0); //run all possible commbinations for a 4 character password
	chars5b(pwdtest, 0); //run all possible commbinations for a 5 character password
	chars6b(pwdtest, 0); //run all possible commbinations for a 6 character password
	chars7b(pwdtest, 0); //run all possible commbinations for a 7 character password
	chars8b(pwdtest, 0); //run all possible commbinations for a 8 character password
	chars9b(pwdtest, 0); //run all possible commbinations for a 9 character password
	chars10b(pwdtest, 0); //run all possible commbinations for a 10 character password
	
	MPI_Finalize();
	return 0;
}

int pwdCheck(char *teststring)
{
	if(strcmp(teststring,pwd) == 0)
	{
		//stop timing
		end=MPI_Wtime();
        return 1;		
    }
    return 0;
}

void match_found(char *pwdtest)
{
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	printf("Match found by node %d!  Pwd = %s\n", my_rank, pwdtest);
	printf("\nTime Elapsed = %f seconds\n", end-start);	
	MPI_Abort(MPI_COMM_WORLD,1);
}

void chars1(char *pwdtest, int index)
{
	int i, match;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		match = pwdCheck(pwdtest);
		if(match) match_found(pwdtest);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		match = pwdCheck(pwdtest);
		if(match) match_found(pwdtest);
	}
}

void chars2a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars1(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars1(pwdtest, index+1);
	}
}


void chars2b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars1(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars1(pwdtest, index+1);
	}
}

void chars3a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars2a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars2a(pwdtest, index+1);
	}
}

void chars3b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars2a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars2a(pwdtest, index+1);
	}
}

void chars4a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars3a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars3a(pwdtest, index+1);
	}
}

void chars4b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars3a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars2a(pwdtest, index+1);
	}
}

void chars5a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars4a(pwdtest, index+1);
	}
		
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars4a(pwdtest, index+1);
	}
}

void chars5b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars4a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars4a(pwdtest, index+1);
	}
}

void chars6a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars5a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars5a(pwdtest, index+1);
	}
}

void chars6b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars5a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars5a(pwdtest, index+1);
	}
}

void chars7a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars6a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars6a(pwdtest, index+1);
	}
}

void chars7b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars6a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars6a(pwdtest, index+1);
	}
}

void chars8a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars7a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars7a(pwdtest, index+1);
	}
}

void chars8b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars7a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars7a(pwdtest, index+1);
	}
}

void chars9a(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=97; i<123; i++)
	{
		pwdtest[index] = (char)i;
		chars8a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=48; i<58; i++)
	{
		pwdtest[index] = (char)i;
		chars8a(pwdtest, index+1);
	}
}

void chars9b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars8a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars8a(pwdtest, index+1);
	}
}

void chars10b(char *pwdtest, int index)
{
	int i;
	
	//chars [a-z]
	for(i=params[0]; i<params[1]; i++)
	{
		pwdtest[index] = (char)i;
		chars9a(pwdtest, index+1);
	}
	
	//chars [0-9]
	for(i=params[2]; i<params[3]; i++)
	{
		pwdtest[index] = (char)i;
		chars9a(pwdtest, index+1);
	}
}
