#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * * argv)
{
	int count;

	for (count = 1; count < argc; count++)
	{
		printf("%s ", argv[count]);
	}

	printf("\n");

	return EXIT_SUCCESS;
}
