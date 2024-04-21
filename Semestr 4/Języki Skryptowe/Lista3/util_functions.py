def sort_log(logs, sort_index):
    if logs is not None:
        try:
            logs[0][sort_index]
        except:
            return None 
        return sorted(logs, key = lambda x: x[sort_index])
    
    return None

def get_entries_by_addr(logs, addr):
    if logs is not None:
        return [x for x in logs if x[1] == addr and 200 <= x[5] < 300]
    return None

def get_entries_by_code(logs, code):
    if logs is not None:
        return [x for x in logs if x[5] == code]
    return None

def get_failed_reads(logs, merge_lists = False):
    bad_logs = []
    error_logs = []

    for log in logs:
        if 400 <= log[5] < 500:
            bad_logs += [log]
        if 500 <= log[5] < 600:
            error_logs += [log]
    
    if merge_lists:
        return bad_logs + error_logs
    return (bad_logs, error_logs)

def get_entries_by_extension(logs, extension):
    if logs is not None:
        return [x for x in logs if x[4].endswith(extension)]
    return None

def print_entries(logs):
    if logs is None:
        return        
    for log in logs:
        print(log)


def entry_to_dict(log):
    return {
        'line': log[0],
        'address': log[1],
        'date': log[2],
        'http_method': log[3],
        'http_link': log[4],
        'http_code': log[5],
        'response_size': log[6]
    }

def log_to_dict(logs):
    log_dict = {}
    
    for log in logs:
        if log[1] not in log_dict:
            log_dict[log[1]] = []
        log_dict[log[1]] += [entry_to_dict(log)]
    
    return log_dict

def get_addrs(logs_dict):
    if logs_dict is not None:
        return list(logs_dict.keys())
    return None

def print_dict_entry_dates(logs_dict):
    print(f'{"Address":<50} {"Entries":<10} {"First Entry":<30} {"Last Entry":<30} {"Success Rate":<30}')

    for key, log_list in logs_dict.items():
        first_date = min(map(lambda x: x['date'], log_list))
        last_date = max(map(lambda x: x['date'], log_list))
        response_with_200 = sum(1 for x in log_list if x['http_code'] == 200)
        response_count = len(log_list)

        print(f'{key:<10} {response_count:<10} {str(first_date):<30} {str(last_date):<30} {response_with_200 / response_count:.2f}')