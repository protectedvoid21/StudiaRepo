from datetime import date, datetime
import re

pattern = r'(\w{3} \d{1,2} \d{2}:\d{2}:\d{2}) (\S+) (\S+)\[(\d+)\]: (.+)'
user_find_regex = r'user\s+(\w+)'

class Log:
    def __init__(self, timestamp: date, host: str, service: str, pid: str, message: str):
        self.timestamp: date = datetime.strptime(timestamp, '%b %d %H:%M:%S').replace(year=datetime.now().year)
        self.host: str = host
        
        user_match = re.search(user_find_regex, message)
        self.user = None
        if user_match:
            self.user = user_match.group(1)
        self.service: str = service
        self.pid: str = pid
        self.message: str = message

    def __str__(self):
        return f'{self.timestamp} {self.host} {self.service}[{self.pid}]: {self.message}'
    

def parse_log(log_entry: str) -> Log:
    match = re.match(pattern, log_entry)

    if not match:
        print(f'Failed to parse log entry: {log_entry}')
        return None
        
    timestamp = match.group(1)
    host = match.group(2)
    service = match.group(3)
    pid = match.group(4)
    message = match.group(5)

    return Log(timestamp, host, service, pid, message)
