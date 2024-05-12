from SSHLogEntry import SSHLogEntry

class SSHLogOther(SSHLogEntry):
    def __init__(self, timestamp: str, host: str, service: str, pid: str, message: str, raw: str):
        super().__init__(timestamp, host, service, pid, message, raw)
        
    def validate(self) -> bool:
        return True