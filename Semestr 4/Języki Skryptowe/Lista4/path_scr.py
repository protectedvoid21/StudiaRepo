import os
import sys


def get_path_files():
    return os.environ['PATH'].split(';')
    
        
def path_contents_with_files():
    paths = get_path_files()
    for path in paths:
        print(path)
        if not os.path.exists(path):
            continue
        for file in os.listdir(path):
            if not os.path.isdir(os.path.join(path, file)):
                print('\t' + file)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        for path in get_path_files():
            print(path)
    else:
        if sys.argv[1] == 'verbose':
            path_contents_with_files()
                