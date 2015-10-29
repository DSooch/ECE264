#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

typedef __uint128_t uint128;

#define FALSE 0
#define TRUE 1 

/**
 * Convert the initial portion of C-string 'str' to an unsigned 128-bit integer
 *
 * This function should be just like atoi(...), except that it returns an 128
 * bit unsigned integer. Return 0 on any error. Don't forget you must skip 
 * white-space.
 *
 * See PA02 for hints on implementing this function.
 */
uint128 alphaTou128(const char * str)
{
	char end = '\0';
	char dash = '-';
	int neg;
	uint128 ret;
	int count;
	int length;
	int started;

	for (length = 0; str[length] != end; length++)
	{
		;
	}

	for (count = 0, ret = 0, neg = 0, started = 0; (count < length) && !started; count++)
	{
		if ((count < length) && (str[count] == dash))
		{
			neg = 1;
			count++;
		}

		while ((str[count] == '0') || (str[count] == '1') || (str[count] == '2') || (str[count] == '3') || (str[count] == '4') || (str[count] == '5') || (str[count] == '6') || (str[count] == '7') || (str[count] == '8') || (str[count] == '9'))
		{
			ret *= 10;
			ret += (str[count] - '0');
			started = 1;
			count++;
		}
	}

	if (neg == 1)
	{
		return (0);
	} else 
	{
		return (ret);
	}
}

/**
 * Return a newly allocated C-string which represents the passed value.
 * The caller is responsible for freeing the allocated string.
 *
 * If you have already implemented alphaTou128(...) (see hint), then you should
 * be able to figure out how to implement u128ToString(...).
 */
char * u128ToString(uint128 value)
{
	int count;
	char digit;
	int length = 0;
	uint128 temp = value;

	while ((temp / 10) > 0)
	{
		temp /= 10;
		length++;
	}

	length += 1;

	char * str = malloc((sizeof(char) * length) + 1);

	for (count = (length - 1); count >= 0; count--)
	{
		digit = (value % 10) + '0';
		str[count] = digit;
		value /= 10;
	}

	str[length] = '\0';
	
	return(str);
}

/**
 * Test is 'value' is prime.
 * 'n_threads' is the number of threads to create to complete this computation.
 * Return TRUE of FALSE.
 * 
 * LEAK NO MEMORY.
 *
 * Good luck!
 */
typedef struct
{
	int startInd;
	int endInd;
	uint128 val;
	int notPrime;
} workerArg;

void * worker(void * arg)
{
	workerArg * newarg = (workerArg *) arg;
	int count;

 	for (count = (newarg -> startInd); (count < (newarg -> endInd)) && ((newarg -> notPrime) != 1) ; count++)
   	{ 
    	if (((newarg -> val) % count) == 0)
     	{
      		newarg -> notPrime = 1;
     	}
  	}
}

int primalityTestParallel(uint128 val, int n_threads)
{
	if (val <= 3 || val == 5 || val == 7)
	{
		return TRUE;
	} else if ((val % 2 == 0) || (val % 3 == 0))
	{
		return FALSE;
	}

	workerArg * args = malloc(sizeof(workerArg) * n_threads);
	pthread_t tags[n_threads];
	uint128 max = floor(sqrt(val));
	int range = max/n_threads;

	int count;
	for (count = 0; count < (n_threads - 1); count++)
	{
		if (count == 0)
		{
			args[count].startInd = 2;
			args[count].endInd = range;
			args[count].val = val;
			args[count].notPrime = 0;
		} else
		{
			args[count].startInd = args[count - 1].startInd + range;
			args[count].endInd = args[count].startInd + range;
			args[count].val = val;
			args[count].notPrime = 0;
		}
	}

	args[n_threads - 1].startInd = max - range;
	args[n_threads - 1].endInd = max;
	args[n_threads - 1].val = val;
	args[n_threads - 1].notPrime = 0;

	for (count = 0; count < n_threads; count++)
	{
		pthread_create(&tags[count], NULL, worker, (void *) &args[count]);
	}

	for (count = 0; count < n_threads; count++)
	{
		pthread_join(tags[count], NULL);
	}

	for (count = 0; count < n_threads; count++)
	{
		if (args[count].notPrime == 1)
		{
			free(args);
			return FALSE;
		}
	}

	free(args);
	return TRUE;
}