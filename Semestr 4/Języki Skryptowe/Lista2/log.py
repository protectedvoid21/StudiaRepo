class Log:
    def __init__(self, line, address, date, http_method, http_link, http_code, response_size):
        self.line = line
        self.address = address
        self.date = date
        self.http_method = http_method
        self.http_link = http_link
        self.http_code = http_code
        self.response_size = response_size

    def __str__(self) -> str:
        return self.line.rstrip()