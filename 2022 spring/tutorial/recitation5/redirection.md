# Redirect
This post will introduce the way our OJ judges your program and will offer you a way to perform a similar test on your PC.
## Basic IO Review
We typically use `scanf`, `getchar`, `gets` to read from standard input (i.e. keyboard); 

And we use `printf`, `putc`, `puts` to write into standard output (i.e. terminal or your screen).

For Files, we typically use `fscanf`, `fgetc`, `fgets` to read from a file;

And we use `fprintf`, `fputc`, `fputs` to write into a file.

## Relation between Standard IO and File IO
```C
scanf(char* fmt, ...)
fscanf(FILE* fp, char* fmt, ...)
printf(char* fmt, ...)
fprintf(FILE* fp, char* fmt, ...)
```
If we compare the parameters of Standard IO function and File IO function, the greatest difference would be an additional parameter called `fp` (whose type is `FILE*`).

Acctually, we may consider `scanf` as a special form of `fscanf` where `fp = stdin`, and `printf` as a special form of `fprintf` where `fp = stdout`. Here, `stdin` and `stdout` are two special file pointers that indicate the keyboard and the terminal (Actually, everthing is file in unix/linux including keyboard and terminal).

Notice that `stdin` and `stdout` are file pointers, we may change the target where `scanf` read from and `printf` write into by changing the file pointers.

We may use `freopen` to do so. For example, to make `scanf` read from `input.txt`, we may use `freopen("input.txt", "r", stdin)`; To make `printf` write into `output.txt`, we may use `freopen("out.txt","w",stdout)`.

Please notice that `freopen` will return the file pointer as `fopen` do, and it will return `NULL` when fault appears.

## Dealing with uncertain lines/length of input
When reading from a FILE or keyboard with uncertain length, we may use `EOF` (which is a macro defined as `-1`) to know if we meet with the end of file. 

For example:
```C
char ch;
while(scanf("%c", &ch) != EOF) {
    // do something
}
// Equivalently
char ch;
while((ch = getchar(stdin)) != EOF) {
    // do something
}
```

## How we acctually judge your program on OJ
In bash, the `stdin` and `stdout` can be redirect to files as well.

On our OJ (actually for almost every OJ), we use redirect to offer input and fetch output of your program.

To simulate such progress on your own PC, you may perform following command:
```
gcc (your_program_name).c -o (output_name)
./(output_name) <input.txt >output.txt
```
Notice that this redirection is perform outside your program, so you don't need to change your code.