#include<stdio.h>

void f(int i ) {
    printf("test in f(): %d ... \n", i);
 }

void g(int i) {
    printf("test in g(): %d ... \n", i);
}

int main(void) {

    int i = 0;
    void (*try)(int) = f;
    try(2022);

    //more pointers
    void(*fa[2])(int) = { f,g };
    fa[0](20);
    fa[1](10);

        for (int i = 0; i < sizeof(fa)/sizeof(fa[0]); i++)
            fa[i](200);

    return 0;
}

