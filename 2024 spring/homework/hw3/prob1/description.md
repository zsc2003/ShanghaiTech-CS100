# Problem 1. Basic knowledge

1. Given the following declarations

```c
int f(void);
int g(void);
```

(1) Which of the following statements is/are true?

{{ multiselect(101) }}

- `f` is a function accepting a parameter of type `void`.
- `f` is a function accepting no parameter and returning `int`.
- `f` is a function that prints a `int`.
- `int x = f;` calls `f` and uses its return value to initialize the variable `x`.

(2) Which of the following statements regarding the expression `printf("%d, %d\n", f(), g())` is true?

{{ multiselect(102) }}

- The call to `g` **may** happen before the call to `f`.
- The call to `f` happens before the call to `g`.
- The return value of `f` **may** be printed before `g` is called.
- Nothing will be printed before the calls to `f` and `g` are done.

2. Select the code snippet(s) that will correctly print `hello` with a newline at the end.

{{ multiselect(2) }}

- ```c
  String s = "hello";
  printf("%s\n", s);
  ```
- ```c
  printf('hello\n');
  ```
- ```c
  const char *str = "hello";
  puts(str);
  ```
- ```c
  puts("hello");
  ```
- ```c
  char str[5] = "hello";
  printf("%s\n", str);
  ```
- ```c
  char str[] = "hello";
  printf("%s\n", str);
  ```

3. The C standard describes the standard library function `strlen` as follows.

> ```c
> size_t strlen(const char *s);
> ```
>
> #### Description
>
> The `strlen` function computes the length of the string pointed to by `s`.

Select the correct understanding(s) about "the string pointed to by `s`".

{{ multiselect(3) }}

- `s` is of type `String *`, which is a pointer to string.
- `s` is of type `const char *`, i.e. a pointer to `const char`, which points to a character.
- `s` is a pointer to `const char`, which can also point to a string because a `char` is a string of length `1`.
- When an array of `char`s is passed to `strlen`, the array is implicitly converted to the address of its first character (indexed `0`), and the parameter `s` is set to be pointing to it.
- A string in C is a sequence of `char`s stored contiguously with a terminating `'\0'`, so we often use a pointer to the first `char` to *represent* the string.

4. Read the following code.

```c
char str[10];
fgets(str, 10, stdin);
```

(1) If the input is `aaabbbcccd` with a newline at the end, what is the content of the string `str`?

{{ select(401) }}

- `"aaabbbcccd"`
- `"aaabbbcccd\n"`
- `"aaabbbccc"`
- `"aaabbbccc\n"`
- Not a valid string, because it does not end with `'\0'`.
- The program has undefined behavior.

(2) If the input is `aaabbbccc` with a newline at the end, what is the content of the string `str`?

{{ select(402) }}

- `"aaabbbccc"`
- `"aaabbbccc\n"`
- `"aaabbbcc\n"`
- Not a valid string, because it does not end with `'\0'`.
- The program has undefined behavior.

(3) If the input is `aaabbbcc` with a newline at the end, what is the content of the string `str`?

{{ select(403) }}

- `"aaabbbcc"`
- `"aaabbbcc\n"`
- Not a valid string, because it does not end with `'\0'`.
- The program has undefined behavior.

(4) If we change `fgets(str, 10, stdin);` to `scanf("%s", str);` and the input is `aaabbbcccd` with a newline at the end, what is the content of the string `str`?

{{ select(404) }}

- `"aaabbbcccd"`
- `"aaabbbcccd\n"`
- `"aaabbbccc"`
- `"aaabbbccc\n"`
- Not a valid string, because it does not end with `'\0'`.
- The program has undefined behavior.

5. Suppose we have allocated some memory as follows.

```c
int *mem = malloc(sizeof(int) * 10);
```

Which of the following code snippets correctly deallocate(s) the memory?

{{ multiselect(5) }}

- ```c
  for (int i = 0; i < 10; ++i)
    free(mem[i]);
  ```
- ```c
  for (int i = 0; i < 10; ++i)
    free(mem + i);
  ```
- ```c
  free(mem);
  ```
- ```c
  free(mem + 5);
  free(mem);
  ```
- ```c
  free(mem, mem + 10);
  ```
- ```c
  free(mem, mem + 10 * sizeof(int));
  ```

6. The standard library function `malloc` is declared as follows.

```c
void *malloc(size_t size);
```

Which of the following statements is/are true?

{{ multiselect(6) }}

- The asterisk (`*`) here is the dereference operator.
- The return type of `malloc` is `void *`.
- The return type of `malloc` is determined at runtime. For example, the return type of `malloc(sizeof(int) * n)` is `int *`.
- If `size > 0`, it will try to allocate at least `size` bytes of memory.
- If `size` is too large, `malloc` will fail and the program will crash.
