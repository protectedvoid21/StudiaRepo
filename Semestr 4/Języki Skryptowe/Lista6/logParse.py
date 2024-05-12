import re
from SSHLogEntry import IPV4_PATTERN, SSHLogEntry
from SSHLogFailure import SSHLogFailure
from SSHLogOther import SSHLogOther
from SSHLogPassAccept import SSHLogPassAccept
from SSHLogPassDenied import SSHLogPassDenied

LOG_PATTERN = r'(\w{3} \d{1,2} \d{2}:\d{2}:\d{2}) (\S+) (\S+)\[(\d+)\]: (.+)'

def parse_log(log_entry: str) -> SSHLogEntry:
    match = re.match(LOG_PATTERN, log_entry)

    if not match:
        print(f'Failed to parse log entry: {log_entry}')
        return None
        
    timestamp = match.group(1)
    host = match.group(2)
    service = match.group(3)
    pid = match.group(4)
    message = match.group(5)
    
    if message.startswith('Failed password'):
        ip = re.findall(IPV4_PATTERN, message)[0]
        port = re.findall(r'port (\d+)', message)[0]
        return SSHLogPassDenied(timestamp, host, service, pid, message, log_entry, ip, port)

    if message.startswith('Accepted password'):
        ip = re.findall(IPV4_PATTERN, message)[0]
        port = re.findall(r'port (\d+)', message)[0]
        return SSHLogPassAccept(timestamp, host, service, pid, message, log_entry, ip, port)
    
    if 'Invalid' in message:
        ip = re.findall(IPV4_PATTERN, message)[0]
        return SSHLogFailure(timestamp, host, service, pid, message, log_entry, ip)

    return SSHLogOther(timestamp, host, service, pid, message, log_entry)