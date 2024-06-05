import math
import string

import pytest

from PasswordGenerator import PasswordGenerator
from funcs import sq_root, make_alpha_dict, flatten

def test_sq_root_of_positive_number():
    assert math.isclose(sq_root(9, 0.0001), math.sqrt(9), rel_tol=0.0001)

def test_sq_root_of_zero():
    assert sq_root(0, 0.0001) == 0

def test_sq_root_of_large_number():
    assert math.isclose(sq_root(1000000, 0.0001), math.sqrt(1000000), rel_tol=0.0001)

def test_sq_root_with_small_epsilon():
    assert math.isclose(sq_root(9, 0.00000001), math.sqrt(9), rel_tol=0.00000001)

def test_sq_root_with_large_epsilon():
    assert math.isclose(sq_root(9, 1), math.sqrt(9), rel_tol=1)

def test_alpha_dict_with_single_word():
    assert make_alpha_dict("word") == {'w': ['word'], 'o': ['word'], 'r': ['word'], 'd': ['word']}

def test_alpha_dict_with_multiple_words_same_letters():
    assert make_alpha_dict("word word") == {'w': ['word', 'word'], 'o': ['word', 'word'], 'r': ['word', 'word'], 'd': ['word', 'word']}

def test_alpha_dict_with_multiple_words_different_letters():
    assert make_alpha_dict("word test") == {'w': ['word'], 'o': ['word'], 'r': ['word'], 'd': ['word'], 't': ['test'], 'e': ['test'], 's': ['test']}

def test_alpha_dict_with_empty_string():
    assert make_alpha_dict("") == {}
    
def test_flatten_empty_list():
    assert flatten([]) == []

def test_flatten_single_level_list():
    assert flatten([1, 2, 3, 4]) == [1, 2, 3, 4]

def test_flatten_nested_list():
    assert flatten([1, [2, 3], 4]) == [1, 2, 3, 4]

def test_flatten_deeply_nested_list():
    assert flatten([1, [2, [3, [4, [5]]]]]) == [1, 2, 3, 4, 5]

def test_flatten_mixed_nested_list():
    assert flatten([1, [2, 3], [4, [5, 6]], 7]) == [1, 2, 3, 4, 5, 6, 7]

def test_flatten_list_with_non_list_elements():
    assert flatten([1, "two", [3, "four"], 5]) == [1, "two", 3, "four", 5]

def tests_password_generator_creates_specified_number_of_passwords():
    pg = PasswordGenerator(10, count=5)
    passwords = list(pg)
    assert len(passwords) == 5

def tests_password_generator_creates_passwords_of_specified_length():
    pg = PasswordGenerator(10)
    password = next(pg)
    assert len(password) == 10

def tests_password_generator_creates_passwords_from_specified_charset():
    charset = string.ascii_uppercase
    pg = PasswordGenerator(10, charset=charset)
    password = next(pg)
    assert all(c in charset for c in password)

def tests_password_generator_raises_stop_iteration_after_count():
    pg = PasswordGenerator(10, count=5)
    with pytest.raises(StopIteration):
        for _ in range(6):
            next(pg)

def tests_password_generator_creates_different_passwords():
    pg = PasswordGenerator(10, count=5)
    passwords = list(pg)
    assert len(set(passwords)) == len(passwords)
    
def tests_password_generator_can_be_used_in_for_each_loop():
    pg = PasswordGenerator(10, count=5)
    passwords = [p for p in pg]
    assert len(passwords) == 5
