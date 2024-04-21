def requests_between_hours(logs, start_hour, end_hour):
    if start_hour > end_hour:
        return
    
    hour_range = range(start_hour, end_hour)
    ranged_requests = []

    for log in logs:
        if log.date.hour in hour_range:
            ranged_requests += [log]

    return ranged_requests