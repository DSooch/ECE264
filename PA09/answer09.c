#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct bnode {
  char * name;
  char * stars;
  char * address;

  struct bnode * left;
  struct bnode * right;
} BusinessNode;

/*
From PA03, used to separate the loaded string from yelp_business.tsv
*/
char * * explode(const char * str, const char * delims)
{
	int count;
	int numDelims;
	char * * strArr;
	int ind;
	int last;
	int arrInd;

	for (count = 0, numDelims = 0; str[count] != '\0'; count++)
	{
		if (strchr(delims, str[count]) != NULL)
		{
			numDelims++;
		}
	}

	strArr = malloc(sizeof(char *) * (numDelims + 1));

	for (last = 0, ind = 0, arrInd = 0; ind < strlen(str); ind++)
	{
		if (strchr(delims, str[ind]) != NULL)
		{
			strArr[arrInd] = malloc(sizeof(char) * (ind - last + 1));

			memcpy(strArr[arrInd], str + last, ind - last);

			strArr[arrInd][ind - last] = '\0';
			
			last = ind + 1;

			arrInd++;
		}
	}

	strArr[arrInd] = malloc(sizeof(char) * (ind - last + 1));

	memcpy(strArr[arrInd], str + last, ind - last);

	strArr[arrInd][ind - last] = '\0';

	return (strArr);
}

/*
 * Construct one BusinessNode. You need to allocate memory for this node first.
 *
 * The caller needs to make sure to use strdup(...) for the arguments, do not
 * use strdup(...) inside of this function.
 *
 * stars: the stars of this business
 * name: name of this business
 * address: address of this business
 */
BusinessNode * create_node(char * stars, char * name, char * address)
{
	BusinessNode * newNode = malloc(sizeof(BusinessNode));
	newNode -> name = name;
	newNode -> stars = stars;
	newNode -> address = address;
	newNode -> left = NULL;
	newNode -> right = NULL;
	return (newNode);
}

/* Insert a node into a BST. Primarily used in load_tree_from_file(). Return a
 * pointer to the root of the BST.
 */
BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
	if (root == NULL)
	{
		root = node;
		return (root);
	}

	if (strcmp(root -> name, node -> name) < 0)
	{
		root -> right = tree_insert(node, root -> right);
	} else if (strcmp(root -> name, node -> name) >= 0)
	{
		root -> left = tree_insert(node, root -> left);
	}

	return (root);
}

/* Parse a .tsv file line by line, create a BusinessNode for each entry, and
 * enter that node into a new BST. Return a pointer to the root of the BST.
 *
 * The explode(...) function from PA03 may be useful for breaking up a lines 
 * into seperate fields. 
 */
BusinessNode * load_tree_from_file(char * filename)
{
	int first = 0;
	char str [1000];
	char * * strExploded;
	BusinessNode * root;
	BusinessNode * node;

	FILE * fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "BAD FILE NAME");
		return (NULL);
	} else
	{
		while (fgets(str, 1000, fp) != NULL)
		{
			strExploded = explode(str, "\t");

			if (first == 0)
			{
				root = create_node(strdup(strExploded[0]), strdup(strExploded[1]), strdup(strExploded[2]));
				first = 1;
			} else 
			{
				node = create_node(strdup(strExploded[0]), strdup(strExploded[1]), strdup(strExploded[2]));
				root = tree_insert(node, root);
			}
			free(strExploded[0]);
			free(strExploded[1]);
			free(strExploded[2]);
			free(strExploded);
		}

	fclose(fp);

	return (root);
	}
}

/* Search a BusinessNode BST for the node with the name 'name'. Returns
 * pointer to the node with a match.
 *
 * If there is no match, return NULL.
 */
BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
	if (root == NULL)
	{
		return (NULL);
	} else if (strcmp(root -> name, name) == 0)
	{
		return (root);
	} else if (strcmp(root -> name, name) < 0)
	{
		root = tree_search_name(name, root -> right);
		return (root);
	} else
	{
		root = tree_search_name(name, root -> left);
		return (root);
	}
}

/* Print out a single node: name, address, and stars
 * The format can be similar to this:
 *
 * Country Cafe
 * ============
 * Stars:
 *    3.5
 * Address:
 *    1030 Emerald Ter, Sun Prairie, WI 53590
 *
 * This function is not graded, but it could come in very handful while
 * debugging this assignment.
 */
void print_node(BusinessNode * node)
{
	fprintf(stdout, "%s\n", node -> name);
	fprintf(stdout, "================\n");
	fprintf(stdout, "Stars:\n");
	fprintf(stdout, "   %s\n", node -> stars);
	fprintf(stdout, "Address:\n");
	fprintf(stdout, "   %s\n", node -> address);
	return;
}

/* Print the entire tree, starting from the root. Like the print_node(...)
 * function, this is not graded.
 */
void print_tree(BusinessNode * tree)
{
	return;
}

/* Deallocate all of the memory used by a BusinessNode BST, without memory
 * leaks.
 */
void destroy_tree(BusinessNode * root)
{
	if (root == NULL)
	{
		return;
	}

	destroy_tree(root -> left);
	destroy_tree(root -> right);

	free(root -> name);
	free(root -> stars);
	free(root -> address);
	free(root);

	return;
}