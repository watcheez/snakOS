import random

print("{", end='')
for i in range(0, 10000):
    print(random.randint(0,8000), ", ", end='')
    if (i % 15 == 0):
        print()
    if (i == 9999):
        print(random.randint(0,8000), "}")
