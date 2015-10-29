#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char * * argv)
{
	int count;
	FILE * fptr;
	int ch;

	for (count = 1; count < argc; count++)
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
			fptr = stdin;

			for (ch = fgetc(fptr); ch != EOF; ch = fgetc(fptr))
			{
				fputc(ch, stdout);
			}
		} else
		{
			fptr = fopen(argv[count], "r");

			if (fptr == NULL)
			{
				fprintf(stderr, "cat cannot open %s\n", argv[count]);
				return EXIT_FAILURE;
			}

			for (ch = fgetc(fptr); ch != EOF; ch = fgetc(fptr))
			{
				fputc(ch, stdout);
			}

			fclose(fptr);
		}
	}

	if (argc == 1)
	{
		fptr = stdin;

		for (ch = fgetc(fptr); ch != EOF; ch = fgetc(fptr))
		{
			fputc(ch, stdout);
		}
	}

	return EXIT_SUCCESS;
}