op = input()
a_str = input()
b_str = input()
a = int(a_str, base=16)
b = int(b_str, base=16)
width = max(len(a_str), len(b_str)) + 1
print(" " * (width - len(a_str)) + a_str)
print(op + " " * (width - len(b_str) - 1) + b_str)
print("-" * width)
result = a + b if op == '+' else a - b
result_str = hex(result)[2:]
print(" " * (width - len(result_str)) + result_str)
