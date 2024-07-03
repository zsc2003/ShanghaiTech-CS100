# Problem 3. Quadratic equation

## Problem description

Solving a linear equation is too hard, so we will solve a quadratic equation. A quadratic equation is of the form $ax^2+bx+c=0$, where $a,b,c$ are constant real numbers and the unknown $x\in\mathbb R$.

Given the coefficients $a,b$ and $c$, your task is to solve the quadratic equation $ax^2+bx+c=0$.

To make the problem easier, $a$ **may be zero**. To make the problem harder, it is guaranteed that $a,b,c\in\mathbb Z$.

Solve the equation and output the solution(s).

- If the equation is a quadratic one, your output should be of one of the following forms (where `???` is replaced with the exact solution):
  - `x1 = x2 = ???`
  - `x1 = ???, x2 = ???` where $x_1<x_2$
  - `No solution.`
- Otherwise, your output should be of one of the following forms (where `???` is replaced with the exact solution):
  - `x = ???`
  - `No solution.`
  - `x\in\mathbb{R}`, indicating $x\in\mathbb R$ in $\LaTeX$

All the output numbers should be rounded to **three decimal places**.

It is guaranteed that $|a|,|b|,|c|\leqslant 100$.

The first five testcases are linear equations. The rest are quadratic equations.

## Examples

### Example 1

Input

```
1 2 1
```

Output

```
x1 = x2 = -1.000
```

### Example 2

Input

```
1 0 1
```

Output

```
No solution.
```

### Example 3

Input

```
0 0 0
```

Output

```
x\in\mathbb{R}
```

### Example 4

Input

```
1 3 2
```

Output

```
x1 = -2.000, x2 = -1.000
```