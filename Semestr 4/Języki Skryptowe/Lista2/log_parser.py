from datetime import date
from log import Log
from parse_date import parse_date

def parse_logs(input_lines: list[str]) -> list[Log]:
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
            http_code = components[8]
            response_size = components[9]
            if str.isnumeric(response_size):
                response_size = int(response_size)
            else:
                response_size = 0
                
            logs += [Log(line, address, req_date, http_method, http_link, http_code, response_size)]
        except:
            error_count += 1

    return logs