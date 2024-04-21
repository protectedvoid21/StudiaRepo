from get_response_extension import get_word_after_last_dot
import sys

from log_parser import parse_logs

def graphic_content_ratio(log_text):
    logs = parse_logs(log_text)

    graphic_ext = { 'gif', 'jpg', 'jpeg', 'xbm' }
    graphic_count = 0

    for log in logs:
        if get_word_after_last_dot(log.http_link) in graphic_ext:
            graphic_count += 1

    print(graphic_count / len(logs))

if __name__ == "__main__":
    graphic_content_ratio(sys.stdin)