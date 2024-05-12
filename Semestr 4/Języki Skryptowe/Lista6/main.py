from SSHLogJournal import SSHLogJournal
from SSHUser import SSHUser

def duck_showcase(journal: SSHLogJournal) -> None:
    entries = journal.select(lambda entry: entry.has_ip)
    user = SSHUser('admin', 'Dec 10 09:20:03')
    
    for _ in range(5):
        entries.append(user)
        
    for entry in entries:
        print(entry.validate())

if __name__ == '__main__':
    journal = SSHLogJournal()
    
    with open('ssh.txt', 'r') as file:
        for line in file:
            journal.append(file.readline())
        
    duck_showcase(journal)
