#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "answer03.h"

int main()
{
	int len = 6
    char * * strArr = malloc(len * sizeof(char*));
    strArr[0] = strdup("1");
    strArr[1] = strdup("2");
    strArr[2] = strdup("3");
    strArr[3] = strdup("4");
    strArr[4] = strdup("5");
    strArr[5] = strdup("6");
    const char * glue = ", ";
    char * s = implode(strArr, len, glue);
	return (0);
}