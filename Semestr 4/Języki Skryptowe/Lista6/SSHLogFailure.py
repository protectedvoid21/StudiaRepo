from SSHLogEntry import SSHLogEntry


class SSHLogFailure(SSHLogEntry):
    def __init__(self, timestamp: str, host: str, service: str, pid: str, message: str, raw: str, ip: str):
        super().__init__(timestamp, host, service, pid, message, raw)
        self.ip: str = ip

    def validate(self) -> bool:
        return True

    def to_json(self) -> dict:
        return {
            'timestamp': self.timestamp.strftime('%Y-%m-%d %H:%M:%S'),
            'host': self.host,
            'service': self.service,
            'pid': self.pid,
            'message': self.message,
            'ipv4': str(self.get_ipv4()),
        }
    
    def __str__(self) -> str:
        return f'{self.timestamp} {self.host} {self.service}[{self.pid}]: {self.message} from {self.ip}'