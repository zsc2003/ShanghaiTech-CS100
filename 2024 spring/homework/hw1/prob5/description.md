# Problem 5. Bus stations

> 说这个正月十五当天下午，在北京城长安街上由东往西来了一辆公共汽车。打始发站出来车上有 6 名乘客。
> 第一站，上来 8 个，下去 2 个。
> 下一站，上来 4 个，下去 5 个。
> 再下一站，上来 10 个，下去 2 个。
> 再下一站，上来 6 个，下去 7 个。
> 再下一站，上来 5 个，下去 9 个。
> 再下一站，上来 1 个，下去 3 个。
> 问这辆公交车一共停了多少站？

Now you are going to write a program to solve this kind of riddles.

## Input format

On the first line, a nonnegative integer $init$ indicating that initially there are $init$ passengers on the bus.

Then several lines follow. The $i$-th line contains two nonnegative integers $out_i$ and $in_i$, meaning that at the $i$-th station $out_i$ passengers get off the bus and $in_i$ passengers get on the bus.

The last line contains a character, which is either `p` or `s` indicating a query (see below).

## Output format

If query is `p`, print the number of passengers in the end.

If query is `s`, print the total number of stations (the initial one is not counted).

Note that the riddle may contain mistakes. If at some station $out_i$ is greater than the current number of passengers on the bus, just print `Impossible.` and terminate the program.

## Notes

The number of lines of input is ***not known***. You may need to make use of the return value of `scanf`. Learn it either by reading [the cppreference documentation](https://en.cppreference.com/w/c/io/fscanf#Return_value) or by doing some experiments.

This problem should be solved without arrays or dynamic memory allocation. Keep your solution simple.

It is guaranteed that the results of all the arithmetic operations involved are representable by the type `int`.

## Examples

### Example 1

Input:

```
6
2 8
5 4
2 10
7 6
9 5
3 1
p
```

Output:

```
12
```

If the last line of input is `s`, the output should be `6`.

### Example 2

Input:

```
2
1 5
8 10
3 4
2 5
s
```

Output:

```
Impossible.
```
