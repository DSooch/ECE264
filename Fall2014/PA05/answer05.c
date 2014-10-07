#include <stdlib.h>
#include <stdio.h>

void printPartition(int * arr, int length)
{
	int count;

	printf("= ");

	for (count = 0; count < (length - 1); count++)
	{
		printf("%d + ", arr[count]);
	}

	printf("%d\n", arr[count]);

	return;
}

//WAS HELPED IN WRITING THIS FUNCTION BY A TA IN THE EE-206 HELP ROOM

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
	if (index == 0)
	{
		return (1);
	}

	if (value > arr[index - 1])
	{
		return (1);
	} else 
	{
		return (0);
	}
}

int decreasing(int value, int * arr, int index)
{
	if (index == 0)
	{
		return (1);
	}

	if (value < arr[index - 1])
	{
		return (1);
	} else 
	{
		return (0);
	}
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
	if (index == 0)
	{
		return (1);
	}

	if ((value % 2 == 0) && (arr[index - 1] % 2 == 1))
	{
		return (1);
	} else if ((value % 2 == 1) && (arr[index - 1] % 2 == 0))
	{
		return (1);
	} else 
	{
		return (0);
	}
}

int prime(int value, int * arr, int index)
{
	int count;

	if (value <= 1)
	{
		return (0);
	}

	for (count = 2; count < value; count++)
	{
		if (value % count == 0)
		{
			return (0);
		}
	}

	return (1);
}

////////////////////////////////////////////////////////////////////////////////

void partitionAll(int value)
{
	int arr[100];
	partitionHelper(arr, 0, value, all);
	return;
}

void partitionIncreasing(int value)
{
	int arr[100];
	partitionHelper(arr, 0, value, increasing);
	return;
}

void partitionDecreasing(int value)
{
	int arr[100];
	partitionHelper(arr, 0, value, decreasing);
	return;
}

void partitionOdd(int value)
{
	int arr[100];
	partitionHelper(arr, 0, value, odd);
	return;
}

void partitionEven(int value)
{
	int arr[100];
	partitionHelper(arr, 0, value, even);
	return;
}

void partitionOddAndEven(int value)
{
	int arr[100];
	partitionHelper(arr, 0, value, oddEven);
	return;
}

void partitionPrime(int value)
{
	int arr[100];
	partitionHelper(arr, 0, value, prime);
	return;
}