#include <stdio.h>
#include <stdlib.h>

template<typename T>
class List
{
private:
	class Node
	{
	public:
		T value;
		Node *next;
	};
	Node *head;

public:
	List() : head(nullptr) {}
    List(const List& src) = delete;
	~List();
	void add(const T& number);
	void print() const;
	bool search(const T& key) const;
	void remove(const T& key);
	void clear();
    List copy();
    List& operator = (const List& src);
};

template<typename T>
List<T> List<T>::copy()
{
    List<T> dest;
	List<T>::Node *p1 = nullptr;
    for (p1 = head; p1; p1 = p1->next)
	{
		dest.add(p1->value);
	}
    return dest;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& src)
{
    clear();
    head = nullptr;
	List<T>::Node *p1 = nullptr;
	for (p1 = src.head; p1; p1 = p1->next)
	{
		add(p1->value);
	}
    return *this;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::add(const T& number)
{
	// List::Node *p = (List::Node *)malloc(sizeof(List::Node));
	List<T>::Node *p = new List<T>::Node;
	p->value = number;
	p->next = NULL;

	// find the last
	List<T>::Node *last = head;
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

template<typename T>
void List<T>::print() const
{
	List<T>::Node *p1 = nullptr;
	int i = 0;
	for (p1 = head; p1; p1 = p1->next)
	{
		printf("link:%p value[%d] = %d...\n",p1, i++, p1->value);
	}
}

template<typename T>
bool List<T>::search(const T& key) const
{
	List<T>::Node *p;
	for (p = head; p; p = p->next)
	{
		if (p->value == key)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
void List<T>::remove(const T& key)
{
	List<T>::Node *p, *q;
	for (q = nullptr, p = head; p; q = p, p = p->next)
	{
		if (p->value == key)
		{
			if (q == nullptr)
				head = p->next;
			else
				q->next = p->next;
			//free(p);
			delete p;
			break;
		}
	}
}

template<typename T>
void List<T>::clear()
{
	List<T>::Node *p, *q;
	for (p = head; p; p = q)
	{
		q = p->next;
		//free(p);
		delete p;
	}
	head = nullptr;
}

int main(int argc, char const *argv[])
{

	List<int> list;
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

	List<int> list_copy;
    list_copy = list;

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
    printf("origin list has removed the key\n");
	list.print();
    printf("The copy still have the key\n");
    list_copy.print();

	// clear
	list.clear();

	return 0;
}
