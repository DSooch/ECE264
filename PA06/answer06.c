#include "answer06.h"
#include <stdlib.h>
#include <stdio.h>
#define SPACE ' '
#define WALL  'X'
#define TRACK '.'
#define MAX_W 100
#define MAX_H 100

int recur(char * * maze, int w, int h, int whitespace, int x, int y, char direction, int first)
{
	int row;
	int col;
	int totperiod = 0;

	for (row = 0; row < h; row++)
	{
		for (col = 0; col < w; col++)
		{
			if (maze[row][col] == '.')
			{
				totperiod++;
			}
		}
	}

	if (whitespace == totperiod)
	{
		return (1);
	}

	if (maze[y][x] != ' ')
	{
		return (0);
	}

	maze[y][x] = '.';

	if (!first)
	{
		printf("%c %d\n", direction, 1);
	}

	first = 0;

	if (x != 0)
	{
		if (recur(maze, w, h, whitespace, x - 1, y, 'W', first))
		{
			return (1);
		}
	}
	if (x != w-1)
	{
		if (recur(maze, w, h, whitespace, x + 1, y, 'E', first))
		{
			return (1);
		}
	}
	if (y != 0)
	{
		if (recur(maze, w, h, whitespace, x, y - 1, 'N', first))
		{
			return (1);
		}
	}
	if (y != h-1)
	{
		if (recur(maze, w, h, whitespace, x, y + 1, 'S', first))
		{
			return (1);
		}
	}

	if (direction == 'N')
	{
		printf("%c %d\n", 'S', 1);
	} else if (direction == 'S')
	{
		printf("%c %d\n", 'N', 1);
	} else if (direction == 'E')
	{
		printf("%c %d\n", 'W', 1);
	} else if (direction == 'W')
	{
		printf("%c %d\n", 'E', 1);
	}

	return(0);
}

void print_directions(char * * maze, int w, int h)
{
	int whitespace = 0;
	int row;
	int col;
	int x;
	int y = 0;
	char direction = 'S';
	int first = 1;

	for (col = 0; col < w; ++col)
	{
		for (row = 0; row < h; ++row)
		{
			if (maze[row][col] == ' ')
			{
				whitespace++;
			}
		}
	}

	for (x = 0; maze[y][x] == 'X'; ++x)
	{
		;
	}	

	recur(maze, w, h, whitespace, x, y, direction, first);

	return;
}