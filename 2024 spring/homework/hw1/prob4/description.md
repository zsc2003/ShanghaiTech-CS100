# Problem 4. Second maximum and second minimum

## Description

In this problem, you need to find the second maximum and second minimum of a series of integers.

Duplicated values should be ignored. For example, the second minimum of $\{1,1,2,3,4\}$ is $2$, not $1$.

## Input format

- The first line contains an integer $n$, indicating that there are $n$ integers. ($n\ge2$)
- The following line contains $n$ integers $x_i$, separated by whitespace.
- For 100% cases, $|x_i|\leq 100$, and there are at least two different numbers.

## Output format

- Two numbers, the second maximum and the second minimum, separated by a whitespace.

## Example

Input:

```
5
3 1 4 7 2
```

Output:

```
4 2
```

## Notes

This problem should be solved without arrays or dynamic memory allocation. Keep your solution simple.

You will not be able to pass the last 5 testcases if you use arrays or dynamic memory allocation.
