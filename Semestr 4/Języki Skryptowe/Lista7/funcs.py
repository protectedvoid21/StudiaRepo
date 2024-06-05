from collections import defaultdict


def acronym(words):
    return str.join('', map(lambda x: x[0], words))


def median(numbers):
    num_sorted = sorted(numbers)

    return num_sorted[len(num_sorted) // 2] if len(num_sorted) % 2 == 1 else (num_sorted[len(num_sorted) // 2] +
                                                                              num_sorted[len(num_sorted) // 2 - 1]) / 2


def sq_root(x, epsilon):
    def helper(n, guess):
        return guess if abs(guess * guess - n) < epsilon else helper(n, (guess + n / guess) / 2)

    return helper(x, x / 2)


def make_alpha_dict(text):
    words = text.split()
    alpha_dict = defaultdict(list)
    list(map(lambda word: list(map(lambda char: alpha_dict[char].append(word), set(word))), words))

    return dict(alpha_dict)


def flatten(lst: list):
    def helper(tail: list, acc: list):
        match tail:
            case []:
                return acc
            case _:
                head, *rest = tail
                return helper(rest, acc + (flatten(head) if isinstance(head, list) else [head]))

    return helper(lst, [])