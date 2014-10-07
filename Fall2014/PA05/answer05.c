#include <stdlib.h>
#include <stdio.h>

#define MAXLEN 100;

void printPartition(int * arr, int length)
{
	int index;

	for (index = 0; index < (length - 1); index++)
	{
		if (index == 0)
		{
			printf("= ");
		} else
		{
			printf("%d + ", arr[index]);
		}
	}

	printf("%d\n", arr[index]);

	return;
}

//WAS HELPED IN WRITING THIS FUNCTION BY A TA IN THE EE 206 HELP ROOM

void partitionHelper(int * buffer, int index, int value, int (* compFunc) (int value, int * arr, int index))
{
	if (value == 0)
	{
		printPartition(buffer, index);
		return;
	}

	int next;
	for (next = 1; next <= value; next++)
	{
		if (compFunc(next, buffer, index))
		{
			buffer[index] = next;
			partitionHelper(buffer, index + 1, value - next, compFunc);
		}
	}
	return;
}

int all(int value, int * arr, int index)
{
	return (1);
}

int increasing(int value, int * arr, int index)
{
	return (0);
}

int decreasing(int value, int * arr, int index)
{
	return (0);
}

int odd(int value, int * arr, int index)
{
	if (value % 2 == 0)
	{
		return (0);
	} else 
	{
		return (1);
	}
}

int even(int value, int * arr, int index)
{
	if (value % 2 == 0)
	{
		return (1);
	} else 
	{
		return (0);
	}
}

int oddEven(int value, int * arr, int index)
{
	return (0);
}

int prime(int value, int * arr, int index)
{
	return (0);
}

////////////////////////////////////////////////////////////////////////////////

void partitionAll(int value)
{
	int arr[MAXLEN];
	partitionHelper(arr, 0, value, all);
	return;
}

void partitionIncreasing(int value)
{
	int arr[MAXLEN];
	partitionHelper(arr, 0, value, increasing);
	return;
}

void partitionDecreasing(int value)
{
	int arr[MAXLEN];
	partitionHelper(arr, 0, value, decreasing);
	return;
}

void partitionOdd(int value)
{
	int arr[MAXLEN];
	partitionHelper(arr, 0, value, odd);
	return;
}

void partitionEven(int value)
{
	int arr[MAXLEN];
	partitionHelper(arr, 0, value, even);
	return;
}

void partitionOddAndEven(int value)
{
	int arr[MAXLEN];
	partitionHelper(arr, 0, value, oddEven);
	return;
}

void partitionPrime(int value)
{
	int arr[MAXLEN];
	partitionHelper(arr, 0, value, prime);
	return;
}