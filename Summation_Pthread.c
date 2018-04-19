//Name: Tellon Smith

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	8
#define SIZE 800
pthread_mutex_t mutexsum;
int numArrayA[SIZE]; //array for numbers (ints)
int numArrayB[SIZE]; //array for numbers (ints)
int globalSum = 0;
//958800
void *BusyWork(void *t)
{
   int i;
   long tid;
   int localSum=0;
   tid = (long)t;
   int start = (tid * 100); 
   int end = (start + 99);
   for (i=start; i<100; i++)
   {
      localSum += numArrayA[i] + numArrayB[i];
   }
   //Lock a mutex prior to updating the value in the shared
   //structure, and unlock it upon updating.
   pthread_mutex_lock (&mutexsum);
   globalSum += localSum;
   printf("Thread %ld did %d to %d:  localsum=%d, current global sum=%d\n",tid,start,end,localSum,globalSum);
   pthread_mutex_unlock (&mutexsum);

   pthread_exit((void*) 0);
}

int main (int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int i =0;
	//initialize array A from zero to n-1
	for (i = 0; i < SIZE; i++)
	{
		numArrayA[i] = i; 
	}
	
	//initialize array B with consecutive even numbers (zero as the first)
	for (i = 0; i < SIZE; i++)
	{
		numArrayA[i] = (i*2); 
	}
	
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	int rc;
	long t;
	void *status;
	
	pthread_mutex_init(&mutexsum, NULL);

   for(t=0;t<NUM_THREADS;t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, BusyWork, (void *)t);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }
 
printf("Final Global sum: %d\n",globalSum);
pthread_exit(NULL);
}
