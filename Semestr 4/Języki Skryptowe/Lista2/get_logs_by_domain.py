from get_response_extension import get_word_after_last_dot


def get_logs_by_domain(logs, domain_set):
    return list(filter(lambda log: get_word_after_last_dot(log.address) in domain_set, logs))