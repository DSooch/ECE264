#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

typedef struct Listnode_temp
{
	char * str;
	struct Listnode_temp * next;
} List;

List * List_createNode(const char * str)
{
	List * newNode = malloc(sizeof(List));
	newNode -> str = strdup(str);
	newNode -> next = NULL;
	return (newNode);
}

void List_destroy(List * list)
{
	if (list == NULL)
	{
		return;
	} else 
	{
		List_destroy(list -> next);

		if (list -> str != NULL)
		{
			free(list -> str);
		}

		free(list);
	}

	return;
}

int List_length(List * list)
{
	List * temp;
	int length;

	if (list == NULL)
	{
		return (0);
	}

	temp = list;
	
	for (length = 0; temp != NULL; ++length)
	{
		temp = list -> next;
		list = temp;
	}

	return (length);

}

List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*))
{
	if (lhs == NULL)
	{
		return (rhs);
	} else if (rhs == NULL)
	{
		return (lhs);
	}

	int val;
	List * head = NULL;
	List * tail = NULL;

	while (lhs != NULL && rhs != NULL)
	{
		val = compar(lhs -> str, rhs -> str);

		if (val > 0)
		{
			if (tail == NULL)
			{
				head = rhs;
				tail = rhs;
			} else 
			{
				tail -> next = rhs;
				tail = rhs;
			}
			rhs = rhs -> next;
			tail -> next = NULL;
		} else
		{
			if (tail == NULL)
			{
				head = lhs;
				tail = lhs;
			} else 
			{
				tail -> next = lhs;
				tail = lhs;
			}
			lhs = lhs -> next;
			tail -> next = NULL;
		}
	}

	if (lhs == NULL)
	{
		tail -> next = rhs;
	} else 
	{
		tail -> next = lhs;
	}

	return (head);
}

List * List_sort(List * list, int (*compar)(const char *, const char*))
{
	int length = List_length(list);
	int halfLength = length / 2;

	if (length <= 1)
	{
		return (list);
	}

	List * lhs = list;
	List * lhsTail = list;

	while (--halfLength > 0)
	{
		lhsTail = lhsTail -> next;
	}

	List * rhs = lhsTail -> next;
	lhsTail -> next = NULL;
	lhs = List_sort(lhs, compar);
	rhs = List_sort(rhs, compar);

	return (List_merge(lhs, rhs, compar));
}