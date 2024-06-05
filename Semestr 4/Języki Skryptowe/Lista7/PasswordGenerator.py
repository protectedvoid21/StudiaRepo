import random
import string


class PasswordGenerator:
    def __init__(self, length, charset=string.ascii_letters + string.digits, count=10):
        self.length = length
        self.charset = charset
        self.count = count
        self.generated_count = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.generated_count >= self.count:
            raise StopIteration
        password = ''.join(random.choices(self.charset, k=self.length))
        self.generated_count += 1
        return password