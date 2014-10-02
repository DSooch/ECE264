#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char * * argv)
{
	int count;
	FILE * fptr;
	int ch;
	int skip;

	for (count = 1, skip = 0; count < argc; count++)
	{
		if (!strcmp(argv[count],"--help"))
		{
			printf("Usage: cat-lite [--help] [FILE]...\n");
			printf("With no FILE, or when FILE is -, read standard input.\n\n");
			printf("Examples:\n");
			printf("  cat-lite README   Print the file README to standard output.\n");
			printf("  cat-lite f - g    Print f's contents, then standard input,\n");
			printf("                    then g's contents.\n");
			printf("  cat-lite          Copy standard input to standard output.\n");
			return EXIT_SUCCESS;
		}

		if (!strcmp(argv[count], "-"))
		{
			skip = 1;
		}

		if (!skip)
		{
			fptr = fopen(argv[count], "r");

			if (fptr == NULL)
			{
				fprintf(stderr, "cat cannot open %s\n", argv[count]);
				return EXIT_FAILURE;
			}

			for (ch = fgetc(fptr); ch != EOF;)
			{
				fputc(ch, stdout);
				ch = fgetc(fptr);
			}

			fclose(fptr);
		}
	}

	return EXIT_SUCCESS;
}