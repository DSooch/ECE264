#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

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
	if (stack -> head == NULL || stack == NULL)
	{
		return TRUE;
	} else 
	{
		return FALSE;
	}
}

/**
 * Pop the front (top) 'value' (i.e. Huffman tree) from the stack.
 *
 * More precisely, this function must do three things:
 * (1) Save the value (i.e. Huffman tree) of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 * (3) Return the value (i.e. Huffman tree) saved in (1).
 */
HuffNode * Stack_popFront(Stack * stack)
{
	HuffNode * val = HuffNode_create(1);

	val = stack -> head -> tree;

	StackNode * temp = malloc(sizeof(StackNode));

	temp = stack -> head -> next;

	HuffNode_destroy(stack -> head -> tree);
	stack -> head -> tree = NULL;
	stack -> head -> next = NULL;

	free(stack -> head);

	stack -> head = temp;

	return (val);
}

/*
 * Push a 'value' (i.e. Huffman tree) onto the front (top) of the stack.
 *
 * More precisely, this function must do two things:
 * (1) Create a new StackNode with 'tree' for its tree.
 * (2) Push that new StackNode onto the front of the stack's list.
 */
void Stack_pushFront(Stack * stack, HuffNode * tree)
{
	StackNode * newNode = malloc(sizeof(StackNode));

	newNode -> tree = HuffNode_create(1);

	newNode -> tree = tree;

	newNode -> next = stack -> head;

	stack -> head = newNode;

	return;
}

// -------------------------------------------------------- Pop Pop combine Push

/**
 * This function helps simplify building a Huffman Coding Tree from the header
 * information. It takes a stack as input. As a precondition, you can assume 
 * that the stack has at least two nodes. This function pops the front (top) 
 * two nodes, combines them into a single node, and pushes the new node back 
 * onto the stack. See Huffman_Coding.pdf to understand conceptually how this
 * should be done.
 */
void Stack_popPopCombinePush(Stack * stack)
{
	HuffNode * first = Stack_popFront(stack);
	HuffNode * second = Stack_popFront(stack);
	HuffNode * final = HuffNode_create(1);

	if (first -> value >= second -> value)
	{
		final -> right = first;
		final -> left = second;

	} else 
	{
		final -> left = first;
		final -> right = second;
	}

	Stack_pushFront(stack, final);
	
	return;
}

// ---------------------------------------------------- Reading HuffTree headers

/**
 * Read a Huffman Coding Tree (in text format) from 'fp'.
 */
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	return;
}

/**
 * Read a Huffman Coding Tree (in binary format) from 'fp'.
 * You will need to (conceptually) read a file a bit at a time. See the README
 * for hints on how to do this.
 */
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	return;
}
