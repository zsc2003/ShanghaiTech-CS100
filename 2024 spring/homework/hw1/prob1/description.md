# Problem 1. Basic knowledge

1. Select the correct statement(s).

{{ multiselect(1) }}

- VSCode and CLion are C/C++ compilers.
- GCC is an operating system.
- C++23 is the latest C++ standard released in 2023. If we want to write code in C++23, we should upgrade VSCode to the latest version.
- A C program can be executed directly by the computer without being transformed into an executable file.
- We can setup our own IDE (Integrated Development Environment) by having VSCode configured with some extensions, compilers and debuggers.

2. Fill in the blanks. For the column "Signedness", write either `signed` or `unsigned`. If the answer to any of the blanks is ***i***mplementation-***d***efined, write `id`.

| Type             | Signedness        | Number of bits at least |
| ---------------- | ----------------- | ----------------------- |
| `char`           | {{ input(2011) }} | {{ input(2012) }}       |
| `signed char`    | {{ input(2021) }} | {{ input(2022) }}       |
| `unsigned char ` | {{ input(2031) }} | {{ input(2032) }}       |
| `short`          | {{ input(2041) }} | {{ input(2042) }}       |
| `unsigned`       | {{ input(2051) }} | {{ input(2052) }}       |
| `int`            | {{ input(2061) }} | {{ input(2062) }}       |
| `long`           | {{ input(2071) }} | {{ input(2072) }}       |
| `long long`      | {{ input(2081) }} | {{ input(2082) }}       |

3. Suppose `int` is 32-bit. Suppose we have the following variable declarations.

```c
int ival = 45;
double dval = 3.14;
unsigned uval = -5;
```

Write down the **type** and the **value** of each of the expressions in the following table. If the type is floating-point, round the value to 2 decimal places. If a type has more than one names, write the shortest one, e.g. write `int` for `signed int`.

| Expression    | Type              | Value             |
| ------------- | ----------------- | ----------------- |
| `ival + dval` | {{ input(3011) }} | {{ input(3012) }} |
| `uval`        | {{ input(3021) }} | {{ input(3022) }} |
| `ival * ival` | {{ input(3031) }} | {{ input(3032) }} |
| `ival / 2.0`  | {{ input(3041) }} | {{ input(3042) }} |
| `-100 / ival` | {{ input(3051) }} | {{ input(3052) }} |

