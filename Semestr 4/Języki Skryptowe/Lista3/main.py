import sys
from util_functions import *
from log_parser import read_log    


if __name__ == "__main__":
    with open('NASA_TEST') as file:
        logs = read_log(file.readlines())
    
    dict_logs = log_to_dict(logs)
    print_dict_entry_dates(dict_logs)