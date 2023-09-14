// Row Wise Block Distributions

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

// the required buffers which will be send to the desired threads
int bufferOne[256][1024] = {0};
int bufferTwo[256][1024] = {0};
int bufferThree[256][1024] = {0};
int bufferFour[256][1024] = {0};

// a function that would be called by the thread
// as row wise then will sum row wise
void *performOperation(void *onBuffer);
void distributeMe(int mainArray[1024][1024], int b1[256][1024], int b2[256][1024], int b3[256][1024], int b4[256][1024]);
bool CorrectOutPutCheck(int mainArray[1024][1024], int distributedSum);

int main()
{
	const int row = 1024;
	const int column = 1024;

	// array decleration
	int mainArray[1024][1024] = {0};

	srand(time(NULL));

	// assigning random values --- the random values in each block
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			// assigning the value
			mainArray[i][j] = rand() % 1025;
		}
	}

	// // distrubiting the array and saving int buffers
	distributeMe(mainArray, bufferOne, bufferTwo, bufferThree, bufferFour);

	// for threads
	pthread_t thread1, thread2, thread3, thread4;

	// for results
	void *resThread1, *resThread2, *resThread3, *resThread4;

	// creating the four threads and giving the desired buffers
	pthread_create(&thread1, NULL, performOperation, (void *)bufferOne);
	pthread_create(&thread2, NULL, performOperation, (void *)bufferTwo);
	pthread_create(&thread3, NULL, performOperation, (void *)bufferThree);
	pthread_create(&thread4, NULL, performOperation, (void *)bufferFour);

	// getting the result
	pthread_join(thread1, &resThread1);
	pthread_join(thread2, &resThread2);
	pthread_join(thread3, &resThread3);
	pthread_join(thread4, &resThread4);

	printf("\n------------------------------------------------------------\n");
	printf("\n Result from  Thread1: %d\n", *(int *)resThread1);
	printf("\n Result from  Thread2: %d\n", *(int *)resThread2);
	printf("\n Result from  Thread3: %d\n", *(int *)resThread3);
	printf("\n Result from  Thread4: %d\n", *(int *)resThread4);

	int finalSum = *(int *)resThread1 + *(int *)resThread2 + *(int *)resThread3 + *(int *)resThread4;

	printf("\n Sum: %d\n", finalSum);
	printf("\n------------------------------------------------------------\n");

	if (CorrectOutPutCheck(mainArray, finalSum))
	{
		printf("\n Sums are Same");
		printf("\n\t     Serial Sum: %d", finalSum);
		printf("\n\t Distribted Sum: %d", finalSum);
	}

	return 0;
}

// for doing the distribution of array accordingly into the buffer
void distributeMe(int mainArray[1024][1024], int b1[256][1024], int b2[256][1024], int b3[256][1024], int b4[256][1024])
{
	int i = 0;

	// for 1st buffer
	for (; i < 256; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			b1[i][j] = mainArray[i][j];
		}
	}

	// for 2nd buffer
	for (; i < 256 * 2; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			b2[i - 256][j] = mainArray[i][j];
		}
	}

	// for 3rd buffer
	for (; i < 256 * 3; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			b3[i - 256 * 2][j] = mainArray[i][j];
		}
	}

	// for 4th buffer
	for (; i < 256 * 4; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			b4[i - 256 * 3][j] = mainArray[i][j];
		}
	}
}

// a function that would be called by the thread
// as row wise then will sum row wise
void *performOperation(void *onBuffer)
{
	// type casting the argument
	int(*b)[1024] = (int(*)[1024])onBuffer;

	// the returnng variable
	int *sum = malloc(sizeof(int));
	*sum = 0;

	// the array of rows sum
	int rowSum[256] = {0};

	// iterating to get rows sum then will sum the row
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			rowSum[i] += b[i][j];
		}
	}

	// calculating the whole sum again by adding whole row
	for (int i = 0; i < 256; i++)
	{
		*sum += rowSum[i];
	}

	// returning the sum of buffer
	return (void *)sum;
}

// for checking the serial sum is same as distribited
bool CorrectOutPutCheck(int mainArray[1024][1024], int distributedSum)
{
	int serialSum = 0;

	// calculating sum
	for (int i = 0; i < 1024; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			serialSum += mainArray[i][j];
		}
	}

	// check the equality
	if (serialSum == distributedSum)
		return true;

	return false; // not same
}
