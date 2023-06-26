// C program to reverse a
// stack using recursion
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// structure of a stack node
struct sNode
{
	char data;
	struct sNode *next;
};

// Function Prototypes
void push(struct sNode** top_ref, int new_data);
int pop(struct sNode** top_ref);
bool isEmpty(struct sNode* top);
void print(struct sNode* top);

// Function to check if the stack is empty
bool isEmpty(struct sNode* top)
{
	return (top == NULL)? 1 : 0;
}

// Below is a recursive function that inserts an element at the bottom of a stack.
void insertAtBottom(struct sNode** top_ref, int item)
{
	if (isEmpty(*top_ref))
		push(top_ref, item);
	else
	{
		// Hold all items in Function Call Stack until we reach end of the
		// stack. When the stack becomes empty, the isEmpty(*top_ref)becomes true,
		// the above if part is executed and the item is inserted at the bottom
		;
		;

		// Once the item is inserted at the bottom, push all
		// the items held in Function Call Stack
		;
	}
}

// Below is the function that reverses the given stack using insertAtBottom()
void reverse(struct sNode** top_ref)
{
	if (!isEmpty(*top_ref))
	{
		// Hold all items in Function Call Stack until we reach end of the stack
		;
		;

		// Insert all the items (held in Function Call Stack) one by one from the bottom
		// to top. Every item is inserted at the bottom
		;
	}
}

// Function to push an item to stack
void push(struct sNode** top_ref, int new_data)
{
	// allocate node
	struct sNode* new_node =(struct sNode*) malloc(sizeof(struct sNode));
	if (new_node == NULL)
	{
		printf("Stack overflow \n");
		exit(0);
	}
	// put in the data
	;
	// link the old list off the new node
	;
	// move the head t point to the new node
	;
}

// Function to print a linked list
void print(struct sNode* top)
{
	;
}

// Function to pop an item from stack
int pop(struct sNode** top_ref)
{
	char res;
	struct sNode *top;

	// If stack is empty then error
	if (*top_ref == NULL)
	{
		printf("Stack overflow \n");
		exit(0);
	}
	else
	{
		;
	}
}

// Main
int main()
{
	struct sNode *s = NULL;
	push(&s, 4);
	push(&s, 3);
	push(&s, 2);
	push(&s, 1);

	printf("\n Original Stack ");
	print(s);
	reverse(&s);
	printf("\n Reversed Stack ");
	print(s);
	return 0;
}
