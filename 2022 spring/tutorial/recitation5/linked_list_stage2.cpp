#include<stdio.h>
#include<stdlib.h>
#include"node.h"

Node* add(Node* head, int number);
void add(Node** phead, int number);

int main(int argc, char const *argv[]) {

	Node *head = NULL;
	int  number;
	do {
		scanf("%d", &number);
		if (number != -1){
			//stage2
			//head = add(head, number);
			//stage2.5
			add(&head, number);
		}
	} while (number != -1);

	// print the link-list
	Node *p1 = NULL;
	int i = 0;
	for (p1 = head ; p1; p1 = p1->next) {
		printf("link-%p-%p: value[%d] = %d...\n", p1, p1->next,i++, p1->value);
	}
	
    // clear
    Node *p, *q;
	for (p = head; p; p = q) {
		q = p->next;
		free(p);
	}
    head = NULL;
	return 0;
}

Node* add(Node* head, int number) {
	// add into the linked-list
	Node *p = (Node*)malloc(sizeof(Node));
	p->value = number;
	p->next = NULL;

	// find the last
	Node *last = head;
	if (last) {
		while (last->next) {
			last = last->next;
		}
		// link
		last->next = p;
	} else {
		head = p;
	}

	return head;
}

void add(Node** phead, int number) {

	Node *p = (Node*)malloc(sizeof(Node));
	p->value = number;
	p->next = NULL;

	// find the last
	Node *last = *phead;
	if (last) {
		while (last->next) { 
			last = last->next;
		}
		// link
		last->next = p;
	}
	else {
		*phead = p;
	}
}