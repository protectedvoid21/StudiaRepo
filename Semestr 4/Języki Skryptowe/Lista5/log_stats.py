import random
import statistics
from log import Log


def random_logs_of_user(logs: list[Log], log_count: int) -> list[Log]:
    random_user = random.choice(list(filter(lambda x: x.user is not None, logs))).user
    
    user_logs = list(filter(lambda x: x.user == random_user, logs))
    random_logs = []
    
    if len(user_logs) < log_count:
        log_count = len(user_logs)
    
    for _ in range(log_count):
        random_logs += [ random.choice(user_logs) ]
        
    return random_logs


def avg_ssh_time(logs_list: list[Log]) -> tuple[float, float]:
    ssh_dict = {}
    
    for log in logs_list:
        if log.pid not in ssh_dict:
            ssh_dict[log.pid] = (log.timestamp, log.timestamp)
        else:
            ssh_dict[log.pid] = (ssh_dict[log.pid][0], log.timestamp)
            
    durations = [log_duration.total_seconds() for log_duration in map(lambda x: x[1] - x[0], ssh_dict.values())]
    
    mean_duration = statistics.mean(durations)
    std_dev_duration = statistics.stdev(durations)

    return mean_duration, std_dev_duration

def most_and_least_occ_user(logs_list: list[Log]) -> tuple[str, str]:
    user_counts = {}
    for log in logs_list:
        if log.user is not None:
            user_counts[log.user] = user_counts.get(log.user, 0) + 1
    
    most_common_user = max(user_counts, key=user_counts.get)
    least_common_user = min(user_counts, key=user_counts.get)
    return most_common_user, least_common_user