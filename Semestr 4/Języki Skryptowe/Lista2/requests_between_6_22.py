from log_parser import parse_logs
from requests_between_hours import requests_between_hours

import sys

def requests_between_6_22(log_text):
    logs = parse_logs(log_text)

    for log in requests_between_hours(logs, 6, 22):
        print(log)

if __name__ == "__main__":
    requests_between_6_22(sys.stdin)