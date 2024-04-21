import datetime
from datetime import datetime

def parse_date(text):
    date_format = '%d/%b/%Y:%H:%M:%S %z'
    return datetime.strptime(text, date_format)

def read_log(input_lines: list[str]):
    logs = []
    line_count = 0
    error_count = 0

    for line in input_lines:
        line_count += 1
        components = line.split()
        
        try:
            address = components[0]
            req_date = parse_date(components[3][1:] + ' ' + components[4][:-1])
            http_method = components[5][1:]
            http_link = components[6]
            http_code = int(components[8])
            response_size = components[9]
            if str.isnumeric(response_size):
                response_size = int(response_size)
            else:
                response_size = 0

            logs += [(line, address, req_date, http_method, http_link, http_code, response_size)]
        except:
            error_count += 1

    return logs