import random
import sys

ALPHABET = list(map(chr, range(33, 127)))

def rand_str(length):
    return "".join(random.choices(ALPHABET, k=length))

n = int(sys.argv[1])
max_length = int(sys.argv[2])
print(n)
for i in range(n):
    length = random.randint(1, max_length)
    print(length)
    if random.choice([False, True]):
        half = rand_str(length // 2)
        s = half
        if length % 2 == 1:
            s += random.choice(ALPHABET)
        s += half[::-1]
        print(s)
    else:
        print(rand_str(length))
