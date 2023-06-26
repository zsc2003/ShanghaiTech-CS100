#include<stdio.h>
#include<stdlib.h>
#include"node.h"

typedef struct _list {
	Node *head;
} List;

void add(List* pList, int number);
void print(List* pList);
bool search(List* pList, int number);
void remove(List* pList, int number);
void clear(List* pList);

int main(int argc, char const *argv[]) {

	List list;
	int  number;
	list.head = NULL;
	
	do {
		scanf("%d", &number);
		if (number != -1) {
			add(&list, number);
		}
	} while (number != -1);

	// print the link-list
	print(&list);

	// search
	printf("input a searched number!\n");
	scanf("%d", &number);

    if (search(&list, number))
        printf("Founded!\n");
    else
        printf("Not Found\n");

    // remove
    remove(&list, number);

	// print again
	print(&list);

	// clear
    clear(&list);

	return 0;
}

void add(List*pList, int number) {
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

void print(List* pList) {
	Node *p1 = NULL;
	int i = 0;
	for (p1 = pList->head; p1; p1 = p1->next) {
		printf("link: value[%d] = %d...\n", i++, p1->value);

	}

}

bool search(List* pList, int number) {
    Node* p;
	for (p= pList->head; p; p=p->next) {
		if (p->value == number){
			printf("found!!!\n");
			return true;
		}
	}
    return false;
}

void remove(List* pList, int number) {
    Node *p,*q;
    for (q = NULL, p = pList->head; p; q = p, p = p->next) {
		if (p->value == number) {
            if (q == NULL)
                pList->head = p->next;
			else
                q->next = p->next; 
			free(p);
			break;
		}
	}
}

void clear(List* pList) {
    Node *p,*q;
	for (p = pList->head; p; p = q) {
		q = p->next;
		free(p);
	}
	pList->head = NULL;
}