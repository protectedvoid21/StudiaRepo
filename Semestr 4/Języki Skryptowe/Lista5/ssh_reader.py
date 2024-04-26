from enum import Enum
from log import Log, parse_log
import logging
import re
import sys

from log_stats import avg_ssh_time, most_and_least_occ_user, random_logs_of_user


def read_logs(lines: list[str]) -> list[Log]:
    logs: list[Log] = []

    for line in lines:
        logs += [parse_log(line)]

    return logs


def get_ipv4s_from_log(log: Log) -> list[str]:
    pattern = r'(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})'
    return re.findall(pattern, log.message)

def get_user_from_log(log: Log) -> str:
    pattern = r'(?<=for\suser\s)(\w+)'
    match = re.search(pattern, log.message)
    return match.group(1) if match else None

class MessageType(Enum):
    ACCEPTED = 1,
    FAILED = 2,
    CONNECTION_CLOSED = 3,
    INVALID_USER = 4,
    INVALID_PASSWORD = 5,
    BREAK_IN_ATTEMPT = 6,
    ERROR = 7,
    OTHER = 8

def get_message_type(message: str) -> MessageType:
    if re.search(r'Accepted', message):
        return MessageType.ACCEPTED
    if re.search(r'Failed', message):
        return MessageType.FAILED
    if re.search(r'Connection closed', message):
        return MessageType.CONNECTION_CLOSED
    if re.search(r'Invalid user', message):
        return MessageType.INVALID_USER
    if re.search(r'Invalid password', message):
        return MessageType.INVALID_PASSWORD
    if re.search(r'BREAK-IN ATTEMPT', message):
        return MessageType.BREAK_IN_ATTEMPT
    if re.search(r'error', message):
        return MessageType.ERROR
    return MessageType.OTHER


logging.basicConfig(level=logging.DEBUG)

def print_log(log: Log):
    logging.debug(f'Read {len(log.message)} bytes')
    message_type = get_message_type(log.message)
    
    if message_type == MessageType.ACCEPTED or message_type == MessageType.CONNECTION_CLOSED:
        logging.info(log.message)
    elif message_type == MessageType.FAILED:
        logging.warning(log.message)
    elif message_type == MessageType.ERROR:
        logging.error(log.message)
    elif message_type == MessageType.BREAK_IN_ATTEMPT:
        logging.critical(log.message)
    else:
        logging.info(log.message)


if __name__ == "__main__":
    logs_text = sys.stdin.readlines()
    logs = read_logs(logs_text)
    
    print(avg_ssh_time(logs))
    