#include "linked_list_macro.h"
#include <stdio.h>
DEF_LIST_DEFS(int);
DEF_LIST_DEFS(char);
void printint(int* x)
{
    printf("%d\n", *x);
}
void printchar(char *x)
{
    printf("%c", *x);
}
void incchar(char *x)
{
    (*x)++;
}
int main()
{
    NEW_LIST(int,mylist);
    LIST_ADD_ELEMENT(int,mylist, 1);
    LIST_ADD_ELEMENT(int,mylist, 1);
    LIST_ADD_ELEMENT(int,mylist, 1);
    LIST_ADD_ELEMENT(int,mylist, 1);
    LIST_ADD_ELEMENT(int,mylist, 1);
    LIST_FOREACH(int,mylist,printint);
    puts("");
    NEW_LIST(char,mylist2);
    LIST_ADD_ELEMENT(char,mylist2, 'A');
    LIST_ADD_ELEMENT(char,mylist2, 'B');
    LIST_ADD_ELEMENT(char,mylist2, 'C');
    LIST_ADD_ELEMENT(char,mylist2, 'D');
    LIST_ADD_ELEMENT(char,mylist2, 'E');
    LIST_FOREACH(char,mylist2,printchar);
    puts("");
    LIST_FOREACH(char,mylist2,incchar);
    LIST_FOREACH(char,mylist2,printchar);
}