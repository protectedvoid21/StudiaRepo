def get_requests_in_day_of_week(logs, weekday_num):
    return list(filter(lambda x: x.date.weekday() == weekday_num, logs))