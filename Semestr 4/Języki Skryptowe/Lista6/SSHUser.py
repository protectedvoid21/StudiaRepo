import datetime
import re

VALIDATE_USER_PATTERN = r'^[a-z_][a-z0-9_-]{0,31}$'


class SSHUser():
    def __init__(self, username: str, date: str):
        self.username: str = username
        self.date: datetime = date
        
    def validate(self) -> bool:
        return re.match(VALIDATE_USER_PATTERN, self.username)
        
        