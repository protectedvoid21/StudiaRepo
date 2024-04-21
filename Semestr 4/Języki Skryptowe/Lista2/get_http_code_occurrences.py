import sys
from log_parser import parse_logs


def get_http_code_occurrences(log_text):
    logs = parse_logs(log_text)

    code_dict = {
        '200': 0,
        '302': 0,
        '404': 0
    }

    for log in logs:
        if log.http_code in code_dict:
            code_dict[log.http_code] += 1

    print(code_dict)

if __name__ == "__main__":
    get_http_code_occurrences(sys.stdin)