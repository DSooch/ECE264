#include <stdlib.h>

size_t my_strlen(const char * str)
{
	int length;
	char end;

	for (end = '\0', length = 0; str[length] != end; length++)
	{
		;
	}

	return(length);
}

int my_countchar(const char * str, char ch)
{
	int count;
	int numch;
	char end;

	for (end = '\0', count = 0, numch = 0; str[count] != end; count++)
	{
		if (str[count] == ch)
		{
			numch++;
		}
	}

	return (numch);
}

char * my_strchr(const char * str, int ch)
{
	int count;
	int length;
	char end;

	for (end = '\0', length = 0; str[length] != end; length++)
	{
		;
	}

	count = 0;

	do
	{
		if (str[count] == ch)
		{
			return (char *) &str[count];
		}
		else if (ch == end)
		{
			return (char *) &str[length];
		}
		count++;
	} while (count < length);

	return (NULL);
}

char * my_strrchr(const char * str, int ch)
{
	int count;
	int length;
	char end;

	for (end = '\0', length = 0; str[length] != end; length++)
	{
		;
	}

	count = length;

	do
	{
		if (str[count] == ch)
		{
			return (char *) &str[count];
		}
		else if (ch == end)
		{
			return (char *) &str[length];
		}
		count--;
	} while (count >= 0);

	return (NULL);
}

char * my_strstr(const char * haystack, const char * needle)
{
	char first = needle[0];
	char end = '\0';
	int hslength;
	int nlength;
	int count;
	int count2;
	int pass;
	int fail;

	for (hslength = 0; haystack[hslength] != end; hslength++)
	{
		;
	}

	for (nlength = 0; needle[nlength] != end; nlength++)
	{
		;
	}

	if (nlength == 0)
	{
		return (char *) &haystack[0];
	}

	for (count = 0, pass = 0; count < hslength; count++)
	{
		if (haystack[count] == first)
		{
			for (count2 = 0, pass = 0, fail = 0; count2 < nlength && !pass && !fail; count2++)
			{
				if (haystack[count + count2] == needle[count2])
				{
					;
				} else
				{
					fail = 1;
				}
				if (count2 == (nlength - 1))
				{
					pass = 1;
				}
			}
		}
		if (pass == 1)
		{
			return (char *) &haystack[count];
		}
	}

	return (NULL);
}

char * my_strcpy(char * dest, const char * src)
{
	int count;
	int srclength;
	char end = '\0';

	for (srclength = 0; src[srclength] != end; srclength++)
	{
		;
	}

	for (count = 0; count <= srclength; count++)
	{
		dest[count] = src[count];
	}

	return (char *) &dest[0];
}

char * my_strcat(char * dest, const char * src)
{
	int count;
	int srccount;
	int destlength;
	int srclength;
	char end = '\0';

	for (destlength = 0; dest[destlength] != end; destlength++)
	{
		;
	}

	for (srclength = 0; src[srclength] != end; srclength++)
	{
		;
	}

	for (count = destlength, srccount = 0; count <= (destlength + srclength); count++, srccount++)
	{
		dest[count] = src[srccount];
	}

	return (char *) &dest[0];
}

int my_isspace(int ch)
{
	int yes = 1;
	int no = 0;

	if (ch == ' ')
	{
		return (yes);
	} else if (ch == '\f')
	{
		return (yes);
	} else if (ch == '\n')
	{
		return (yes);
	} else if (ch == '\r')
	{
		return (yes);
	} else if (ch == '\t')
	{
		return (yes);
	} else if (ch == '\v')
	{
		return (yes);
	} else
	{
		return (no);
	}
}

int my_atoi(const char * str)
{
	char end = '\0';
	char dash = '-';
	int neg;
	int ret;
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
		return (-ret);
	} else 
	{
		return (ret);
	}
}