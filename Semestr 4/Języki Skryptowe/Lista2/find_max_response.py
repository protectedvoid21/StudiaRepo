import sys
from log import Log
from log_parser import parse_logs

def find_max_response(log_text):
    logs = parse_logs(log_text)
    biggest_log = logs[0]

    for log in logs:
        if log.response_size > biggest_log.response_size:
            biggest_log = log

    print(biggest_log)

if __name__ == "__main__":
    find_max_response(sys.stdin)