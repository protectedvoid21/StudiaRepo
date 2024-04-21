from datetime import datetime


def parse_date(text):
    date_format = '%d/%b/%Y:%H:%M:%S %z'
    return datetime.strptime(text, date_format)