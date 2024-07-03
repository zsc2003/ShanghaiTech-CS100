# Problem 2. Sum and maximum

## Description

Class Exercise 1

Write a program that reads an unknown number of integers from input until 0 is entered. Print the sum and the maximum of these integers.

## Input format

Several lines, the $i$-th of which is an integer $s_i$. The last line is `0`.

- For 100% cases, $|s_i|\leq 100$.
- All the integers before the last line are nonzero.

## Output format

Two lines:

```
sum: xxx
maximum: yyy
```

where `xxx` and `yyy` are replaced with the sum and the maximum of the input integers. Note that the terminating `0` is not counted.

## Examples

### Example 1

Input:

```
1
2
3
0
```

Output:

```
sum: 6
maximum: 3
```

### Example 2

Input:

```
-1
-2
-3
0
```

Output:

```
sum: -6
maximum: -1
```

## Notes

This problem should be solved without arrays or dynamic memory allocation. Keep your solution simple.
