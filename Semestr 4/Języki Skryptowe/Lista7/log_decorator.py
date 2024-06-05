import functools
import logging
import time


def log(level):
    def decorator_log(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            start_time = time.time()
            result = func(*args, **kwargs)
            end_time = time.time()
            duration = end_time - start_time

            logger = logging.getLogger(func.__name__)
            logger.setLevel(level)
            handler = logging.StreamHandler()
            formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
            handler.setFormatter(formatter)
            logger.addHandler(handler)

            logger.log(level, f"Called function {func.__name__} with arguments {args} {kwargs}. "
                              f"Function returned {result}. Execution time: {duration} seconds.")
            return result
        return wrapper
    return decorator_log