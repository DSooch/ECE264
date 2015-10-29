 #include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
	int count;
	int sum;

	for (count = 0, sum = 0; count < len; count++)
	{
		sum += array[count];
	}

	return(sum);
}

int arrayCountNegative(int * array, int len)
{
	int numNeg;
    int count;
     
	for (count = 0, numNeg = 0; count < len; count++)
	{
		if (array[count] < 0)
		{
			numNeg++;
		}
	}
    return (numNeg);
}

int arrayIsIncreasing(int * array, int len)
{  
	int count;
	int yes;
	int no;

	for (yes = 1, no = 0, count = 1; count < len; count++)
	{
		if(array[count - 1] > array[count])
		{
			return(no);
		}
	}

    return(yes);
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
	int count;
	int index;

	for (count = 0, index = -1; count < len; count++)
	{
		if (haystack[count] == needle)
		{
			index = count;
		}
	}

    return (index);
}

int arrayFindSmallest(int * array, int len)
{
	int count;
	int smallestIndex;
	int smallest;

	if (len == 0)
	{
		return (0);
	}

	for(count = len - 1, smallest = array[len - 1]; count >= 0; count--)
	{
		if (array[count] <= smallest)
		{
			smallest = array[count];
         	smallestIndex = count;
		}
	}

    return (smallestIndex);
}