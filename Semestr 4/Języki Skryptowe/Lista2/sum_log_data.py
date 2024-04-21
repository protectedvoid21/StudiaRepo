import sys
from log import Log
from log_parser import parse_logs

BYTES_IN_GB = 1073741824

def sum_log_data(log_text):
    logs = parse_logs(log_text)
    print(sum(log.response_size for log in logs) / BYTES_IN_GB)

if __name__ == "__main__":
    sum_log_data(sys.stdin)