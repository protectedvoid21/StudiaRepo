from get_requests_in_day_of_week import get_requests_in_day_of_week

import sys

from log_parser import parse_logs

def get_requests_in_friday(log_text):
    logs = parse_logs(log_text)

    for log in get_requests_in_day_of_week(logs, 4):
        print(log)

if __name__ == "__main__":
    get_requests_in_friday(sys.stdin)