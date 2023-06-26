#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    struct car { char *make; char *model; int year; }; // declares the struct type
    // declares and initializes an object of a previously-declared struct type
    struct car c = { .make="Nash", .model="48 Sports Touring Car",.year=1923};
    printf("car: %d %s %s\n", c.year, c.make, c.model);
 
    // declares a struct type, an object of that type, and a pointer to it
    //ship = {"Incom Corporation", "T-65 X-wing starfighter", "128 ABY"},
    typedef struct spaceship { char *make; char *model; char *year; } spaceship;
    spaceship *pship = malloc(sizeof(spaceship));
    pship->make="Incom Corporation";pship->model="T-65 X-wing starfighter";pship->year="128 ABY";
    printf("spaceship: %s %s %s\n", pship->year, pship->make, pship->model);
 
    // addresses increase in order of definition
    // padding may be inserted
    struct A { char a; double b; char c;};
    printf("offset of char a = %zu\noffset of double b = %zu\noffset of char c = %zu\n"
           "sizeof(struct A) = %zu\n", offsetof(struct A, a), offsetof(struct A, b),
           offsetof(struct A, c), sizeof(struct A));
    //#pragma pack(1) padding
    struct B { char a; char b; double c;};
    printf("offset of char a = %zu\noffset of char b = %zu\noffset of double c = %zu\n"
           "sizeof(struct B) = %zu\n", offsetof(struct B, a), offsetof(struct B, b),
           offsetof(struct B, c), sizeof(struct B));
 
    // A pointer to a struct can be cast to a pointer to its first member and vice versa
    char* pmake = (char*)pship;
    pship = (struct spaceship *)pmake;

    free(pship);
    return 0;
}