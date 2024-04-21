import sys

from log_parser import parse_logs


def filter_200_response(log_text):
    logs = parse_logs(log_text)
    for log in filter(lambda x: x.http_code == '200', logs):
        print(log.line)

if __name__ == "__main__":
    filter_200_response(sys.stdin)