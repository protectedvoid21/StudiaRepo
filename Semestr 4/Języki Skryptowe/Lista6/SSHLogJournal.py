from typing import Callable
from SSHLogEntry import SSHLogEntry
from logParse import parse_log

class SSHLogJournal:
    def __init__(self) -> None:
        self._entries: list[SSHLogEntry] = []
    
    def append(self, raw_entry: str) -> None:
        entry = parse_log(raw_entry)
        if entry:
            self._entries.append(entry)
            
    def __len__(self) -> int:
        return len(self._entries)
    
    def __getitem__(self, index: int) -> SSHLogEntry:
        return self._entries[index]
    
    def __iter__(self):
        return iter(self._entries)
    
    def __str__(self) -> str:
        return '\n'.join(str(entry) for entry in self._entries)
    
    def select(self, selector: Callable[[SSHLogEntry], bool]) -> list[SSHLogEntry]:
        return [entry for entry in self._entries if selector(entry)]