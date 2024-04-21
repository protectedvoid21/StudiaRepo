def get_word_after_last_dot(text):
    text_splited = text.split('.')
    
    if len(text_splited) <= 1:
        return ''

    return text_splited[-1]