#include <stdio.h>
#include <stdlib.h>

class List
{
private:
	class Node
	{
	public:
		int value;
		Node *next;
	};
	Node *head;

public:
	List() : head(nullptr) {}
	~List();
	void add(int number);
	void print() const;
	bool search(int key) const;
	void remove(int key);
	void clear();
};

List::~List()
{
	clear();
}

void List::add(int number)
{
	// List::Node *p = (List::Node *)malloc(sizeof(List::Node));
	List::Node *p = new List::Node;
	p->value = number;
	p->next = NULL;

	// find the last
	List::Node *last = head;
	if (last)
	{
		while (last->next)
		{
			last = last->next;
		}
		// link
		last->next = p;
	}
	else
	{
		head = p;
	}
}

void List::print() const
{
	List::Node *p1 = nullptr;
	int i = 0;
	for (p1 = head; p1; p1 = p1->next)
	{
		printf("link: value[%d] = %d...\n", i++, p1->value);
	}
}

bool List::search(int key) const
{
	List::Node *p;
	for (p = head; p; p = p->next)
	{
		if (p->value == key)
		{
			return true;
		}
	}
	return false;
}

void List::remove(int key)
{
	List::Node *p, *q;
	for (q = nullptr, p = head; p; q = p, p = p->next)
	{
		if (p->value == key)
		{
			if (q == nullptr)
				head = p->next;
			else
				q->next = p->next;
			// free(p);
			delete p;
			break;
		}
	}
}
void List::clear()
{
	List::Node *p, *q;
	for (p = head; p; p = q)
	{
		q = p->next;
		// free(p);
		delete p;
	}
	head = NULL;
}

int main(int argc, char const *argv[])
{

	List list;
	int number;

	do
	{
		scanf("%d", &number);
		if (number != -1)
		{
			list.add(number);
		}
	} while (number != -1);

	// print the link-list
	list.print();

	// search
	printf("input a searched number!\n");
	scanf("%d", &number);

	if (list.search(number))
		printf("Founded!\n");
	else
		printf("Not Found\n");

	// remove
	list.remove(number);

	// print again
	list.print();

	// clear
	list.clear();

	return 0;
}
