import sys
from get_logs_by_domain import get_logs_by_domain


def get_requests_from_poland(logs):
    for log in get_logs_by_domain(logs, { 'pl' }):
        print(log)