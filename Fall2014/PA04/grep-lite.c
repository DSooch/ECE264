#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char * * argv)
{
	int count;
	int invert;
	int lines;
	int quiet;
	FILE * fptr;
	char * pattern;
	int linenum;
	char line[2000];
	int found;

	pattern = argv[argc - 1];

	if (argv[argc - 1][0] == '-')
	{
		fprintf(stderr, "invalid PATTERN argument");
		return (2);
	}

	for (count = 1, invert = 0, lines = 0, quiet = 0; count < (argc - 1); count++)
	{
		if (!strcmp(argv[count],"--help"))
		{
			printf("Usage: grep-lite [OPTION]... PATTERN\n");
			printf("Search for PATTERN in standard input. PATTERN is a\n");
			printf("string. grep-lite will search standard input line by\n");
			printf("line, and (by default) print out those lines which\n");
			printf("contain pattern as a substring.\n\n");
  			printf("  -v, --invert-match     print non-matching lines\n");
  			printf("  -n, --line-number      print line numbers with output\n");
 			printf("  -q, --quiet            suppress all output\n\n");
			printf("Exit status is 0 if any line is selected, 1 otherwise\n");
			printf("if any error occurs, then the exit status is 2.\n");
			return EXIT_SUCCESS;
		}

		if (!strcmp(argv[count], "-v") || !strcmp(argv[count], "--invert-match"))
		{
			invert++;
		}

		if (!strcmp(argv[count], "-n") || !strcmp(argv[count], "--line-number"))
		{
			lines++;
		}

		if (!strcmp(argv[count], "-q") || !strcmp(argv[count], "--quiet"))
		{
			quiet++;
		}
	}

	fptr = stdin;

	for (linenum = 1, found = 0; fgets(line, 2000, fptr) != NULL; linenum++)
	{
		if (strstr(line, pattern) == NULL)
		{
			if (invert > 0)
			{
				found++;
			}
			if (lines > 0 && !quiet && invert > 0)
			{
				fprintf(stdout, "%d:", linenum);
				fputs(line, stdout);
				found++;
			} else if (lines == 0 && !quiet && invert > 0)
			{
				fputs(line, stdout);
				found++;
			}
		} else 
		{	
			if (invert == 0)
			{
				found++;
			}
			if (lines > 0 && !quiet && invert == 0)
			{
				fprintf(stdout, "%d:", linenum);
				fputs(line, stdout);
				found++;
			} else if (lines == 0 && !quiet && invert == 0)
			{
				fputs(line, stdout);
				found++;
			}
		}
	}

	if (found > 0)
	{
		return (0);
	} else
	{
		return (1);
	}
}