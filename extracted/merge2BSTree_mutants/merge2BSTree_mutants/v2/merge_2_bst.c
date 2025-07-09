//This program is taken from the website: https://www.geeksforgeeks.org/merge-two-bsts-with-limited-extra-space/


#include<stdio.h> 
#include<stdlib.h> 

// Structure of a BST Node 
struct node 
{ 
	int data; 
	struct node *left; 
	struct node *right; 
}; 

//.................... START OF STACK RELATED STUFF.................... 
// A stack node 
struct snode 
{ 
	struct node *t; 
	struct snode *next; 
}; 

// Function to add an elemt k to stack 
void push(struct snode **s, struct node *k) 
{ 
	struct snode *tmp = (struct snode *) malloc(sizeof(struct snode)); 

	//perform memory check here 
	tmp->t = k; 
	tmp->next = *s; 
	(*s) = tmp; 
} 

// Function to pop an element t from stack 
struct node *pop(struct snode **s) 
{ 
	struct node *t; 
	struct snode *st; 
	st=*s; 
	(*s) = (*s)->next; 
	t = st->t; 
	free(st); 
	return t; 
} 

// Fucntion to check whether the stack is empty or not 
int isEmpty(struct snode *s) 
{ 
	if (s == NULL ) 
		return 1; 

	return 0; 
} 
//.................... END OF STACK RELATED STUFF.................... 


/* Utility function to create a new Binary Tree node */
struct node* newNode (int data) 
{ 
	struct node *temp = (struct node*)malloc(sizeof(struct node)); 
	temp->data = data; 
	temp->left = NULL; 
	temp->right = NULL; 
	return temp; 
} 

/* A utility function to print Inoder traversal of a Binary Tree */
void inorder(struct node *root) 
{ 
	if (root != NULL) 
	{ 
		inorder(root->left); 
		printf("%d ", root->data); 
		inorder(root->right); 
	} 
} 

// The function to print data of two BSTs in sorted order 
void merge(struct node *root1, struct node *root2) 
{ 
	// s1 is stack to hold nodes of first BST 
	struct snode *s1 = NULL; 

	// Current node of first BST 
	struct node *current1 = root1; 

	// s2 is stack to hold nodes of second BST 
	struct snode *s2 = NULL; 

	// Current node of second BST 
	struct node *current2 = root2; 

	// If first BST is empty, then output is inorder 
	// traversal of second BST 
	if (root1 == NULL) 
	{ 
		inorder(root2); 
		return; 
	} 
	// If second BST is empty, then output is inorder 
	// traversal of first BST 
	if (root2 == NULL) 
	{ 
		inorder(root1); 
		return ; 
	} 

	// Run the loop while there are nodes not yet printed. 
	// The nodes may be in stack(explored, but not printed) 
	// or may be not yet explored 
	while (current1 != NULL || !isEmpty(s1) || 
		current2 != NULL || !isEmpty(s2)) 
	{ 
		// Following steps follow iterative Inorder Traversal 
		if (current1 != NULL || current2 != NULL ) 
		{ 
			// Reach the leftmost node of both BSTs and push ancestors of 
			// leftmost nodes to stack s1 and s2 respectively 
			if (current1 != NULL) 
			{ 
				push(&s1, current1); 
				current1 = current1->left; 
			} 
			if (current2 != NULL) 
			{ 
				push(&s2, current2); 
				current2 = current2->left; 
			} 

		} 
		else
		{ 
			// If we reach a NULL node and either of the stacks is empty, 
			// then one tree is exhausted, ptint the other tree 
			if (isEmpty(s1)) 
			{ 
				while (!isEmpty(s2)) 
				{ 
					current2 = pop (&s2); 
					current2->left = NULL; 
					inorder(current2); 
				} 
				return ; 
			} 
			if (isEmpty(s2)) 
			{ 
				while (!isEmpty(s1)) 
				{ 
					current1 = pop (&s1); 
					current1->left = NULL; 
					inorder(current1); 
				} 
				return ; 
			} 

			// Pop an element from both stacks and compare the 
			// popped elements 
			current1 = pop(&s1); 
			current2 = pop(&s2); 

			// If element of first tree is smaller, then print it 
			// and push the right subtree. If the element is larger, 
			// then we push it back to the corresponding stack. 
			if (current1->data < current2->data) 
			{ 
				printf("%d ", current1->data); 
				current1 = current1->right; 
				push(&s2, current2); 
				current2 = NULL; 
			} 
			else
			{ 
				printf("%d ", current2->data); 
				current2 = current2->right; 
				push(&s1, current1); 
				current1 = NULL; 
			} 
		} 
	} 
} 

/* Driver program to test above functions */
int main(int argc, int* argv[]) 
{ 
	struct node *root1 = NULL, *root2 = NULL; 

	/* Let us create the following tree as first tree 
			3 
		/ \ 
		1 5 
	*/
	int p,q,r,s,t,u, max,min,rest;
	p=atoi(argv[1]);
	q=atoi(argv[2]);
	r=atoi(argv[3]);
	s=atoi(argv[4]);
	t=atoi(argv[5]);
	u=atoi(argv[6]);
	
	max= p > q ? (p > r ? p : r) : (q > r ? q : r); 
	min= p < q ? (p < r ? p : r) : (q < r ? q : r); 
	rest=(p+q+r)-(min+max);
	root1 = newNode(rest); 
	root1->left = newNode(min); 
	root1->right = newNode(max); 

	/* Let us create the following tree as second tree 
			4 
		/ \ 
		2 6 
	*/

	max= s > t ? (s > u ? s : u) : (t > u ? t : u); 
	min= s < t ? (s < u ? s : u) : (t < u ? t : u); 
	rest=(s+t)-(min+max);
	root2 = newNode(rest); 
	root2->left = newNode(min); 
	root2->right = newNode(max);
 

	// Print sorted nodes of both trees 
	merge(root1, root2); 

	return 0; 
} 

