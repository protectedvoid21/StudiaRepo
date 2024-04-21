import sys


def take_last_lines(lines: list[str], count: int = 10):
    if len(lines) == 0:
        return None
    return lines[-count:]


def parse_args(args: list[str]) -> [str, int]:
    if len(args) == 0:
        return None, 10
    if len(args) == 1:
        if args[0].startswith('--lines='):
            return None, parse_lines(args[0])
    
    if len(args) == 2:
        if args[0].startswith('--lines='):
            return args[1], parse_lines(args[0])
        return args[0], parse_lines(args[1])
    return None


def parse_lines(line_text: str) -> int | None:
    split_by_equals = line_text.split('=')
    if len(split_by_equals) != 2:
        return None

    try:
        line_num = int(split_by_equals[1])
    except ValueError:
        raise ValueError('Invalid format for --lines argument. Must be --lines=<number>')
        
    if line_num < 0:
        raise ValueError('Number of lines must be positive')
    return line_num


def strip_each(words: list[str]) -> list[str]:
    return list(map(lambda x: x.rstrip(), words))

if __name__ == '__main__':
    text, line_count = parse_args(sys.argv[1:])
    
    if text is None:
        text = strip_each(sys.stdin.readlines())
    else:
        with open(text, 'r') as file:
            text = strip_each(file.readlines())

    print(take_last_lines(text, line_count))
