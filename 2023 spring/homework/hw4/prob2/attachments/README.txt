destructor.c:
    The code for you to play with `__attribute__((destructor))`.

line_and_file.c:
    The code for you to play with `__LINE__` and `__FILE__`.

my_code.c, sample1.c, sample2.c:
    Three sample programs.

memcheck.h:
    The file that you need to complete and submit.

testcases:
    Almost the same with the testcases on OJ. (But they do have differences. Don't try to hardcode the results.) You can run the `.c` files and see whether their outputs are identical to the corresponding `.out` files.

    The testcase `fhq_treap` has an input file `fhq_treap.in`, and `stdin` of `fhq_treap.c` has been redirected to it using the `freopen` function. `fhq_treap.c` is a piece of code that can pass Luogu P3369.

    All the `.out` and `.in` files are plain test files, which can be opened using any code editor (including VSCode, of course).

    The `.c` files use `#include "../memcheck.h"` instead of `#include "memcheck.h"`, because `memcheck.h` is placed in the parent directory of `testcases` (`..` means parent directory).