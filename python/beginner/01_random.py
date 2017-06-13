
from __future__ import print_function

import random

# Generate a pseudo-random number between 0 and 1.
print('# Generate a pseudo-random number between 0 and 1.')
print(random.random())
print()

# Pick a random number between 1 and 100. Integer
print('# Pick a random number between 1 and 100.')
print(random.randint(1, 100))
print('# Pick another random number between 1 and 100.')
x = random.randint(1, 100)
print(x)

# Pick a random number between 1 and 10, float
print('# Pick a random float number between 1 and 10.')
print(random.uniform(1, 10))
print()

# Shuffle a list
print('Shuffle a list.')
items = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print('before shuffle:', items)
random.shuffle(items)
print('after shuffle:', items)
print()

# Sample items from list
print('Sample from list:', items)
x = random.sample(items, 1)
print('Sample 1 item: ', x[0])
y = random.sample(items, 4)
print('Sample 4 items: ', y)
print()

names = ['Zhang San', 'Li Si', 'Wang Wu', 32, 3.25, ('My Age', 15)]
print(random.sample(names, 1))
print(random.sample(names, 4))
print()

