from SSHLogEntry import SSHLogEntry
from SSHLogPassword import SSHLogPassword


class SSHLogPassDenied(SSHLogPassword):
    def __init__(self, timestamp: str, host: str, service: str, pid: str, message: str, raw: str, ip: str, port: str):
        super().__init__(timestamp, host, service, pid, message, raw, ip, port)
        
    def validate(self) -> bool:
        return self.message.startswith('Failed password')