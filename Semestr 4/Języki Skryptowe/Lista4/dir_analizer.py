import subprocess
import os
import sys
import json

analyzer_path = "C:\\Users\\niezn\\OneDrive\\Pulpit\\Studia\\StudiaRepo\\Semestr 4\\Języki Skryptowe\\Lista4\\Zad4\\bin\\Debug\\net8.0\\Zad4.exe"

class FileInfo:
    def __init__(self, file_path: str, character_count: int, word_count: int, line_count: int, most_occ_char: str, most_occ_word: str): 
        self.file_path = file_path
        self.character_count = character_count
        self.word_count = word_count
        self.line_count = line_count
        self.most_occ_char = most_occ_char
        self.most_occ_word = most_occ_word
        
    def __str__(self):
        return (f'File: {self.file_path}\nCharacter count: {self.character_count}\nWord count: {self.word_count}'
                f'\nLine count: {self.line_count}\nMost common character: {self.most_occ_char}\n'
                f'Most common word: {self.most_occ_word}\n')

def json_to_fileinfo(json_string) -> FileInfo:
    data = json.loads(json_string)
    file_path = data.get('FilePath')
    character_count = int(data.get('CharacterCount'))
    word_count = int(data.get('WordCount'))
    line_count = int(data.get('LineCount'))
    most_occ_char = data.get('MostOccurrentChar')
    most_occ_word = data.get('MostOccurrentWord')
    
    return FileInfo(file_path, character_count, word_count, line_count, most_occ_char, most_occ_word)
    

def analyze_directory(dir_path: str):
    if not os.path.exists(dir_path) or not os.path.isdir(dir_path):
        print('Directory does not exist!')
        return

    if not os.path.exists(analyzer_path):
        print('Analyzer does not exist!')
        
    files = os.listdir(dir_path)

    file_results = {}

    for file_path in files:
        full_path = os.path.join(dir_path, file_path)
        if not os.path.isfile(full_path):
            print(full_path + ' is not a file!')
            continue
        
        process = subprocess.run([analyzer_path], stdout=subprocess.PIPE, input=full_path.encode())

        if process.returncode != 0:
            print('Something went wrong with analyzing file: ' + full_path)
            continue
            
        file_data = json_to_fileinfo(process.stdout)
        file_results[file_path] = file_data
        
    return file_results

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Directory path was not provided!')
    elif len(sys.argv) > 2:
        print('Too many arguments passed!')
    else:
        file_results = analyze_directory(sys.argv[1])
        
        character_sum = 0
        word_sum = 0
        line_sum = 0
        
        for file_name, file_info in file_results.items():
            character_sum += file_info.character_count
            word_sum += file_info.word_count
            line_sum += file_info.line_count
            
        print(f'Character sum: {character_sum}\nWord sum: {word_sum}\nLine sum: {line_sum}')