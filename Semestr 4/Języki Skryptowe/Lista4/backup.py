import os
import sys
import subprocess
import json
import hashlib
from datetime import datetime

backup_dir_path = os.getenv('BACKUPS_DIR', f'C://Users//{os.getlogin()}//.backup')


def generate_hash(text):
    hash_object = hashlib.sha256()
    hash_object.update(text.encode())
    
    return hash_object.hexdigest()


def save_backup_history(dir_path, archive_name, file_hash):
    history_file_path = os.path.join(backup_dir_path, f'{dir_path}_{file_hash}_history.json')

    dir_history_json = {
        'dir_name': dir_path,
        'archive_name': archive_name,
        'path': os.path.abspath(dir_path),
        'backup_date': datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    }
    
    if not os.path.exists(history_file_path):
        with open(history_file_path, 'w') as f:
            json.dump([dir_history_json], f)
    else:
        with open(history_file_path, 'r') as f:
            history = json.load(f)
            history.append(dir_history_json)
            
        with open(history_file_path, 'w') as f:
            json.dump(history, f)


def archive_files(dir_path):
    if not os.path.exists(dir_path):
        print(f"Error: Directory '{dir_path}' does not exist")
        return
    
    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    file_hash = generate_hash(dir_path)
    archive_name = f'{timestamp}-{dir_path}-{file_hash}.zip'
    subprocess.run(["powershell", "-Command", f"Compress-Archive -Path {dir_path} -DestinationPath {archive_name}"])
    
    if not os.path.exists(backup_dir_path):
        os.mkdir(backup_dir_path)
        
        
    subprocess.run(['powershell', '-Command', f'Move-Item -Path {archive_name} -Destination {backup_dir_path}'])
    
    save_backup_history(dir_path, archive_name, file_hash)
    

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python backup.py <filename>")
        sys.exit(1)
        
    dir_path = sys.argv[1]
    
    archive_files(dir_path)