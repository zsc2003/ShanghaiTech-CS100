# Problem 1. Basic knowledge

1. Suppose `c` is a variable of type `char`. If `c` is a decimal digit character, how can we obtain its numeric value?

{{ multiselect(1) }}

- `int(c)`
- `parseInt(c)`, where `parseInt` is a standard library function.
- `c - 48`
- `c - '0'`
- `c - '\0'`
- `odr(c) - '0'`, where `odr` is a standard library function that is used to obtain the ASCII value of `c`.
- `*(int *)&c`

2. Regarding **undefined behaviors**, which of the following statements is/are true?

{{ multiselect(2) }}

- An undefined behavior results in one of a set of valid results. For example, the following code (assuming `int` is 32-bit) will assign the variable `x` with some value, but we don't know what the value is.
  
  ```c
  int ival = 10000000;
  int x = ival * ival;
  ```
- An undefined behavior means that there are no restrictions on the behavior of the program. The standard does not require such programs to do anything meaningful.
- An undefined behavior means that two or more behaviors are permitted by the standard and that the compiler will choose a meaningful one. The behavior remains unchanged when the program is run again, although we don't know what the behavior is.
- Correct C programs shall not have undefined behaviors.

3. Suppose `int` is 32-bit and `long long` is 64-bit. Select the code snippet(s) that involve(s) integer overflow.

{{ multiselect(3) }}

- ```c
  int x = 42 / 0;
  ```
- ```c
  int ival = 1000000;
  long long llval = ival * ival;
  ```
- ```c
  unsigned uval = -42;
  ```
- ```c
  unsigned u1 = 10000000;
  unsigned u2 = u1 * u1;
  ```

4. Select the code snippet(s) that involve(s) undefined behavior.

{{ multiselect(4) }}

- ```c
  int random(void) {
    int x;
    return x;
  }
  int main(void) {
    printf("%d\n", random());
  }
  ```
- ```c
  unsigned uval = -5;
  printf("%u\n", uval);
  ```
- ```c
  int table[100];
  int exists_in_table(int value) {
    for (int i = 0; i <= 100; ++i)
      if (table[i] == value)
        return 1;
    return 0;
  }
  ```
- ```c
  int foo(int value) {
    printf("%d\n", value);
  }
  int main(void) {
    int x = 42;
    int y = foo(x);
    printf("%d\n", x + y);
  }
  ```
- ```c
  int i = 42;
  printf("%d\n", i, i++);
  ```
- ```c
  double pi = 3.14;
  printf("%d\n", pi);
  ```

5. Read the following code.

```c
void swap(int *pa, int *pb) {
  int tmp = *pa;
  *pa = *pb;
  *pb = tmp;
}
int main(void) {
  int x = 10, y = 15;
  swap(&x, &y);
  printf("%d %d\n", x, y);
}
```

(1) Which of the following statements is/are true?

{{ multiselect(501) }}

- The asterisk (`*`) in the function parameter declaration `int *pa` is a part of `int *`, meaning that `pa` is a pointer to `int`.
- The asterisk (`*`) in the statement `int tmp = *pa` is the dereference operator, which is used to access the object that `pa` points to.
- The asterisk (`*`) in the statement `*pb = tmp` is the pointer symbol, meaning that `pb` is a pointer.
- The asterisk (`*`) in the statement `*pb = tmp` is the dereference operator, which is used to access the object that `pb` points to.

(2) Which of the following statements is/are true?

{{ multiselect(502) }}

- If we rewrite the function `swap` as follows
  
  ```c
  void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
  }
  ```

  and replace `swap(&x, &y)` with `swap(x, y)` in the `main` function, the values of `x` and `y` are still exchanged successfully.
- The parameter declarations of `swap` can be rewritten as `int *pa, pb`, because `pa` and `pb` are of the same type.
- The parameter declarations of `swap` can be rewritten as `int *pa, *pb`, because `pa` and `pb` are of the same type.
- The function `swap` will output the values of `*pa` and `*pb`.
- None of the above.

(3) Write down the type of each expression. For pointer types, place exactly one space between the pointee type and the first asterisk, and no spaces between consecutive asterisks (e.g. `int *`, `int **`, or `int ***`, but not `int*` or `int * *`).

| Expression | `pa`              | `*pa`             | `&pa`             | `x`               | `&x`              |
| ---------- | ----------------- | ----------------- | ----------------- | ----------------- | ----------------- |
| Type       | {{ input(5031) }} | {{ input(5032) }} | {{ input(5033) }} | {{ input(5034) }} | {{ input(5035) }} |

6. Read the following code.

```c
int min_element(int *array, int l, int r) {
  int pos = l;
  while (l < r) {
    if (array[l] < array[pos])
      pos = l;
    ++l;
  }
  return pos;
}

int a[] = {1, 4, 2, 8, 5, 7};
```

(1) Which of the following statements is/are true?

{{ multiselect(601) }}

- `min_element(array, l, r)` returns $\min\{$ `array[i]` $\mid i\in[l,r)\}$.
- `min_element(array, l, r)` returns $\min\{$ `array[i]` $\mid i\in[l,r]\}$.
- `min_element(array, l, r)` returns the index of the first occurrence of $\min\{$ `array[i]` $\mid i\in[l,r)\}$.
- `min_element(array, l, r)` prints the index of the first occurrence of $\min\{$ `array[i]` $\mid i\in[l,r)\}$ to the standard output.
- To make `min_element(array, l, r)` return the index of the last occurrence of $\min\{$ `array[i]` $\mid i\in[l,r)\}$, replace `array[l] < array[pos]` (on line 4) with `array[l] <= array[pos]`.

(2) Suppose we have the following `main` function.

```c
int main(void) {
  printf("%d\n", min_element(a, 0, 6));
}
```

Which of the following statements is/are true?

{{ multiselect(602) }}

- The function `main` contains undefined behavior.
- The type of the parameter `array` is `int [6]`.
- The type of the parameter `array` is `int []`, where the length is determined at run-time and may change.
- The type of the parameter `array` is `int *`.
- Since we want to find the minimum element in the entire array `a`, we can simply write `min_element(a)`, and the parameters `l` and `r` will be assigned with `0` and `6` automatically.

7. Given the functions `swap` and `min_element` as defined in the previous two questions. Read the following code.

```c
void sort(int *array, int n) {
  for (int i = 0; i < n - 1; ++i) {
    int min_pos = min_element(array, i, n);
    swap(&array[i], &array[min_pos]);
    // Note: If you have difficulty understanding this function, uncomment the following lines, run the code and look at the output.
    // for (int i = 0; i < n; ++i)
    //   printf("%d ", a[i]);
    // printf("\n");
  }
}
int main(void) {
  int a[] = {8, 5, 7, 1, 4, 2};
  sort(a, 6);
  for (int i = 0; i < 6; ++i)
    printf("%d ", a[i]);
  printf("\n");
}
```

(1) Regarding the `sort` function, which of the following statements is/are true?

{{ multiselect(701) }}

- `swap(&array[i], &array[min_pos])` is equivalent to `swap(array + i, array + min_pos)`.
- At each iteration, the smallest element in `{array[i], ..., array[n - 1]}` is found and then placed at index `i` by swapping with `array[i]`.
- The effect of `sort` on the array is not changed if we rewrite the loop condition as `i < n`.
- `sort(array, n)` sorts the elements `{array[0], ..., array[n - 1]}` in non-decreasing order.

(2) Which of the following statements is/are true?

{{ multiselect(702) }}

- The program prints `1 2 4 5 7 8 `.
- If we replace `sort(a, 6)` as `sort(a, 4)`, the output becomes `1 2 4 5 8 7 `.
- If we replace `sort(a, 6)` as `sort(a, 3)`, the output becomes `5 7 8 1 4 2 `.
- If we replace `sort(a + 2, 4)`, the output becomes `8 5 1 2 4 7 `, i.e. only the last four elements are sorted.
