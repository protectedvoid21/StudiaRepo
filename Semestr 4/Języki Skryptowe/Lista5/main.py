import sys

from log_stats import avg_ssh_time
from ssh_reader import read_logs


if __name__ == "__main__":
    logs_text = sys.stdin.readlines()[200:]
    logs = read_logs(logs_text)
    
    print(avg_ssh_time(logs))
    