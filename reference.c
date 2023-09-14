// Row Wise Block Distribution ---> Domain Decomposition

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>

// a function that would be called by the thread
// as row wise then will sum row wise 
void *performOperation(void * onBuffer)
{
	sleep(1);
	int* a = malloc(sizeof(int));
	*a = 0;
	printf("Printing GeeksQuiz from Thread \n");
	return (void *)a;
}


int main()
{
	void* a;
	pthread_t thread_id;
	pthread_create(&thread_id, NULL,performOperation, NULL);
	pthread_join(thread_id, &a);

	
	printf( "LLLLLLL %.2f", *(int*)a);

	exit(0);
}


// // Row Wise Block Distribution ---> Domain Decomposition

// // libraries
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h> 
// #include <pthread.h>

// // a function that would be called by the thread
// // as row wise then will sum row wise 
// void *performOperation(void * onBuffer);
// void distributeMe(int ** mainArray, int**distributedArrays);

// int main()
// {
// 	const int row = 1024;
// 	const int column = 1024;

// 	// array decleration
// 	int mainArray[row][column] = {0};
	
// 	srand(time(NULL));

// 	// assigning random values --- the random values in each block
// 	for(int i=0; i < row; i++)
// 	{
// 		for(int j=0; j<row;j++)
// 		{
// 			// assigning the value
// 			mainArray[i][j] = rand() % 1025;
// 		}

// 		printf("\n");
// 	}
	
// 	// distrubiting the array 
	
	
// 	return 0;
// }

// // for doing the distribution of array accordingly into the buffer
// void distributeMe(int ** mainArray, int**distributedArrays)
// {

// }

// // a function that would be called by the thread
// // as row wise then will sum row wise 
// void *performOperation(void * onBuffer)
// {

// }