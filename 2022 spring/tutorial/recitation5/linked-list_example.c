//-------------------------------------------------
// example-1

#include<stdio.h>
#include<stdlib.h>
#include"node.h"

Node* add(Node* head, int number);
void add(Node** phead, int number);

int main(int argc, char const *argv[]) {

	Node *head = NULL;
	int  number;
	do
	{
		scanf("%d", &number);
		if (number != -1){
#if 0

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
			}
			else {
				head = p;
			}
#else
			// head = add(head, number);
			add(&head, number);
#endif
		}

	} while (number != -1);

	// print the link-list
	Node *p1 = NULL;
	int i = 0;
	for (p1 = head ; p1; p1 = p1->next){
		printf("link-%p-%p: value[%d] = %d...\n", p1, p1->next,i++, p1->value);
	}


	return 0;
}

Node* add(Node* head, int number)
{
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
	}
	else {
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
//-------------------------------------------------
// example-2
#include<stdio.h>
#include<stdlib.h>
#include"node.h"

typedef struct _list {
	Node *head;

} List;

void add(List* pList, int number);
void print(List* pList);

int main(int argc, char const *argv[]) {

	List list;
	int  number;
	list.head = NULL;

	do
	{
		scanf("%d", &number);
		if (number != -1){
			add(&list, number);
		}

	} while (number != -1);

	// print the link-list
	print(&list);

	return 0;
}

void add(List*pList, int number)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->value = number;
	p->next = NULL;

	// find the last
	Node *last = pList->head;
	if (last) {
		while (last->next) {
			last = last->next;
		}
		// link
		last->next = p;
	}
	else {
		pList->head = p;
	}
}

void print(List* pList)
{
	Node *p1 = NULL;
	int i = 0;
	for (p1 = pList->head; p1; p1 = p1->next) {
		printf("link: value[%d] = %d...\n", i++, p1->value);

	}

}



//-------------------------------------------------
// example-3
#include<stdio.h>
#include<stdlib.h>
#include"node.h"

typedef struct _list {
	Node *head;

} List;

void add(List* pList, int number);
void print(List* pList);

int main(int argc, char const *argv[]) {

	List list;
	int  number;
	list.head = NULL;

	do
	{
		scanf("%d", &number);
		if (number != -1){
			add(&list, number);
		}

	} while (number != -1);

	// print the link-list
	print(&list);

	// search
	printf("input a searched number!\n");
	scanf("%d", &number);

	Node *p;
	int isFound = 0;
	for (p= list.head; p; p=p->next){
		if (p->value == number){
			printf("found!!!\n");
			isFound = 1;
			break;
		}
	}
	if (!isFound){
		printf("not found!!!\n");
	}

	Node *q;
	for (q = NULL, p = list.head; p; q = p, p = p->next) {
		if (p->value == number){
			q->next = p->next; // bug,why?
			//list.head = p->next; 
			free(p);	
			break;
		}
	}

	// print again
	print(&list);

	// clear
	for (p = list.head; p; p = q) {
		q = p->next;
		free(p);
	}

	return 0;
}

void add(List*pList, int number)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->value = number;
	p->next = NULL;

	// find the last
	Node *last = pList->head;
	if (last) {
		while (last->next) {
			last = last->next;
		}
		// link
		last->next = p;
	}
	else {
		pList->head = p;
	}
}

void print(List* pList)
{
	Node *p1 = NULL;
	int i = 0;
	for (p1 = pList->head; p1; p1 = p1->next) {
		printf("link: value[%d] = %d...\n", i++, p1->value);

	}

}



