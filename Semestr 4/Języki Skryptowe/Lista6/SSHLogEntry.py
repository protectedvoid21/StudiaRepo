from datetime import date, datetime
from ipaddress import IPv4Address
import re
from abc import ABC, abstractmethod

IPV4_PATTERN = r'(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})'
FIND_USER_PATTERN = r'user\s+(\w+)'

class SSHLogEntry(ABC):
    def __init__(self, timestamp: date, host: str, service: str, pid: str, message: str, raw: str):
        self.timestamp: date = datetime.strptime(timestamp, '%b %d %H:%M:%S').replace(year=datetime.now().year)
        self.host: str = host
        
        user_match = re.search(FIND_USER_PATTERN, message)
        self.user = None
        if user_match:
            self.user = user_match.group(1)
        self.service: str = service
        self.pid: str = pid
        self.message: str = message
        self.raw: str = raw

    @property
    def has_ip(self) -> bool:
        return bool(re.findall(IPV4_PATTERN, self.message))
        
    @has_ip.getter
    def has_ip(self) -> bool:
        return bool(re.findall(IPV4_PATTERN, self.message))
        
    @abstractmethod
    def validate() -> bool:
        ...
        
    def get_ipv4(self) -> IPv4Address:
        ip_text = re.findall(IPV4_PATTERN, self.message)
        return IPv4Address(ip_text[0]) if ip_text else None
    
    def to_json(self) -> dict:
        return {
            'timestamp': self.timestamp.strftime('%Y-%m-%d %H:%M:%S'),
            'host': self.host,
            'service': self.service,
            'pid': self.pid,
            'message': self.message,
            'user': self.user,
            'ipv4': str(self.get_ipv4())
        }

    def __str__(self) -> str:
        return f'{self.timestamp} {self.host} {self.service}[{self.pid}]: {self.message}'
    
    def __repr__(self) -> str:
        return self.__str__()
    
    def __eq__(self, other) -> bool:
        return str(self) == str(other)
    
    def __lt__(self, other) -> bool:
        return self.timestamp < other.timestamp
    
    def __gt__(self, other) -> bool:
        return self.timestamp > other.timestamp
