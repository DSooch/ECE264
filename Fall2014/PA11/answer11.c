#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ONE 49
#define ZERO 48

// -------------------------------------------------------------------- HuffNode

typedef struct leaf 
{
    int value;
    struct leaf * left;  // left sub-tree
    struct leaf * right; // right sub-tree
} HuffNode;

typedef struct StackNode_st
{
    HuffNode * tree;
    struct StackNode_st * next;
} StackNode;

typedef struct Stack_st
{
    StackNode * head; // head node of a linked-list
} Stack;

HuffNode * HuffNode_create(int value)
{
	HuffNode * newNode = malloc(sizeof(HuffNode));
	newNode -> value = value;
	newNode -> left = NULL;
	newNode -> right = NULL;

	return (newNode);
}

void HuffNode_destroy(HuffNode * tree)
{
	if (tree == NULL)
	{
		return;
	}

	HuffNode_destroy(tree -> left);
	HuffNode_destroy(tree -> right);

	free(tree);

	return;
}

// ----------------------------------------------------------------------- Stack

Stack * Stack_create()
{
	Stack * new = malloc(sizeof(Stack));
	new -> head = NULL;

	return (new);
}

void destroy(StackNode * list)
{
	if (list == NULL)
	{
		return;
	}

	destroy(list -> next);

	HuffNode_destroy(list -> tree);
	free(list);

	return;
}

void Stack_destroy(Stack * stack)
{
	if (stack == NULL)
	{
		return;
	}

	destroy(stack -> head);

	free(stack);

	return;
}

int Stack_isEmpty(Stack * stack)
{
	if (stack == NULL)
	{
		return TRUE;
	} else if (stack -> head == NULL)
	{
		return TRUE;
	} else 
	{
		return FALSE;
	}
}

HuffNode * Stack_popFront(Stack * stack)
{
	HuffNode * val = stack -> head -> tree;

	StackNode * temp = stack -> head -> next;

	free(stack -> head);

	stack -> head = temp;

	return (val);
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
	StackNode * newNode = malloc(sizeof(StackNode));

	newNode -> tree = tree;

	newNode -> next = stack -> head;

	stack -> head = newNode;

	return;
}

void Stack_popPopCombinePush(Stack * stack)
{
	HuffNode * first = Stack_popFront(stack);
	HuffNode * second = Stack_popFront(stack);
	HuffNode * final = HuffNode_create(1);

	final -> left = second;
	final -> right = first;

	Stack_pushFront(stack, final);
	
	return;
}

// ---------------------------------------------------- Reading HuffTree headers

/**
 * Read a Huffman Coding Tree (in text format) from 'fp'.
 */
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	int ch;
	int done = 0;

	Stack * stack = Stack_create();

	while (!done)
	{
		if (fgetc(fp) == '1')
		{
			ch = fgetc(fp);

			HuffNode * new = HuffNode_create(ch);

			Stack_pushFront(stack, new);
		} else 
		{
			if (stack -> head -> next == NULL)
			{
				done = 1;
			} else
			{
				Stack_popPopCombinePush(stack);
			}
		}
	}

	HuffNode * final = stack -> head -> tree;

	free(stack -> head);

	free(stack);

	return (final);
}

/**
 * Read a Huffman Coding Tree (in binary format) from 'fp'.
 * You will need to (conceptually) read a file a bit at a time. See the README
 * for hints on how to do this.
 */
int readBit(FILE * fp, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte)
{
	int ret = 1;
	if ((* whichbit) == 0)
	{
		ret = fread(curbyte, sizeof(unsigned char), 1, fp);
	}
	if (ret != 1)
	{
		return (-1);
	}

	unsigned char temp = (* curbyte) >> (7 - (* whichbit));
	temp = temp & 0X01;
	* whichbit = ((* whichbit) + 1) % 8;
	* bit = temp;
	return 1;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	int done = 0;
	unsigned char whichbit = 0;
	unsigned char curbyte = 0;
	unsigned char onebit = 0;
	Stack * stack = Stack_create();

	while (done == 0)
	{
		readBit(fp, & onebit, & whichbit, & curbyte);
		if (onebit == 1)
		{
			int bitcount;
			unsigned char value = 0;
			for (bitcount = 0; bitcount < 8; bitcount++)
			{
				value <<= 1;
				readBit(fp, & onebit, & whichbit, & curbyte);
				value |= onebit;
			}
			HuffNode * hn = HuffNode_create(value);
			Stack_pushFront(stack, hn);
		} else
		{
			if (stack == NULL)
			{
				printf("Error, stack should not be NULL\n");
			}
			if ((stack -> head -> next) == NULL)
			{
				done = 1;
			} else
			{
				Stack_popPopCombinePush(stack);
			}
		}
	}

	HuffNode * final = stack -> head -> tree;

	free(stack -> head);

	free(stack);

	return (final);
}