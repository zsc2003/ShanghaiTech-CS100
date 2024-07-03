# Problem 4. 6174

The number $6174$ is known as **Kaprekar's constant** after the Indian mathematician D. R. Kaprekar. This number is renowned for the following rule:

1. Take any four-digit number, using at least two different digits (leading zeros are allowed).
2. Arrange the digits in descending and then in ascending order to get two four-digit numbers, adding leading zeros if necessary.
3. Subtract the smaller number from the bigger number.
4. Go back to step 2 and repeat.

The above process, known as *Kaprekar's routine*, will always reach its fixed point, 6174, in at most 7 iterations. Once 6174 is reached, the process will continue yielding $7641 - 1467 = 6174$. For example, choose $1459$:

$$
\begin{aligned}
  9541&-1459&=8082\\
  8820&-288&=8532\\
  8532&-2358&=6174
\end{aligned}
$$

Write a program that simulates this process. Note that

- The input number should not contain more than 4 digits and should contain at least two different digits (i.e. not a *repdigit* like $1111$, $2222$, ...). These numbers are said to be ***invalid***.
- The input number may contain less than 4 digits. For example, start with $9$:

  $$
  \begin{aligned}
    9000&-9&=8991\\
    9981&-1899&=8082\\
    8820&-288&=8532\\
    8532&-2358&=6174
  \end{aligned}
  $$

## Hint

The functions given in **[Problem 1] Basic knowledge** may be helpful for this problem.

## Input format

On the first line, a nonnegative integer $n$.

Then $n$ lines follow, the $i$-th of which contains a nonnegative integer $x_i$. It is guaranteed that $x_i$ is representable by `int`.

## Output format

For each of the $n$ input integers, either report that it is invalid or simulate the Kaprekar's routine and print the steps (see below).

If for some $i$ the integer $x_i$ contains more than 4 digits, print `xxx contains more than 4 digits.` where `xxx` is replaced with $x_i$. If $x_i$ contains no more than 4 digits but is a *repdigit*, print `xxx is a repdigit.` where `xxx` is replaced with $x_i$.

A step in the Kaprekar's routine should be printed in the form `xxx - yyy = zzz`, where `xxx`, `yyy` and `zzz` are replaced with the corresponding numbers. Note that leading zeros **are not printed** (see the example below). The process stops when `zzz` reaches $6174$.

If the input is already $6174$, you should print nothing and start processing next input.

**You don't have to start printing after all inputs are consumed!** Do not waste efforts saving the things to be printed.

## Example

Input

```
5
123456
0
22
4444
1459
```

Output

```
123456 contains more than 4 digits.
0 is a repdigit.
2200 - 22 = 2178
8721 - 1278 = 7443
7443 - 3447 = 3996
9963 - 3699 = 6264
6642 - 2466 = 4176
7641 - 1467 = 6174
4444 is a repdigit.
9541 - 1459 = 8082
8820 - 288 = 8532
8532 - 2358 = 6174
```
