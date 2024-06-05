import functools
import logging
import time

import log_decorator


def make_generator(func):
    def generator():
        n = 1
        while True:
            yield func(n)
            n += 1

    return generator


@log_decorator.log(logging.INFO)
def fibonacci(n):
    if n <= 2:
        return 1
    else:
        a, b = 1, 1
        for _ in range(3, n + 1):
            a, b = b, a + b
        return b


fibonacci_gen = make_generator(fibonacci)

for num in fibonacci_gen():
    if num > 100:
        break
    print(num)

print()

for num in make_generator(lambda x: x * 3 + x)():
    if num > 100:
        break
    print(num)


def make_generator_mem(func):
    func = functools.lru_cache(maxsize=None)(func)

    def generator():
        n = 1
        while True:
            yield func(n)
            n += 1

    return generator

