import os
import sys

for param in sys.argv[1:]:
    for key, value in os.environ.items():
        if param.upper() in key:
            print(key + " = " + value)