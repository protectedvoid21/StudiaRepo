import json
import os
import subprocess
import sys

backup_dir_path = os.getenv('BACKUPS_DIR', os.getcwd())

def analize_history(history_file_path):
    with open(history_file_path, 'r') as f:
        history = json.load(f)
        
    return history


def print_history(history):
    index = 1
    for item in history:
        print(f'#{index}---|')
        print(f"     |Directory: {item['dir_name']}")
        print(f"     |Archive: {item['archive_name']}")
        print(f"     |Path: {item['path']}")
        print(f"     |Backup date: {item['backup_date']}")
        print()
        index += 1
        
            
def restore_backup(backup):
    backup_path = os.path.join(backup_dir_path, backup['archive_name'])
    
    if not os.path.exists(backup_path):
        print(f"Error: File '{backup_path}' does not exist")
        sys.exit(1)
        
    dest_path = os.path.join(str.join('\\', backup["path"].split('\\')[:-1]))
    print(dest_path)
    subprocess.run(['powershell', '-Command', f'Expand-Archive -Force -Path "{backup_path}" -DestinationPath "{dest_path}"'])


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python restore.py <filename>")
        sys.exit(1)
        
    filename = sys.argv[1]
    history_file_path = os.path.join(backup_dir_path, filename)
    
    if not os.path.exists(history_file_path):
        print(f"Error: File '{history_file_path}' does not exist")
        sys.exit(1)
        
    history = analize_history(history_file_path)
    print_history(history)
    
    backup_index = int(input("Enter the number of the backup you want to restore: "))
    
    if backup_index < 1 or backup_index > len(history):
        print("Error: Invalid backup number")
        sys.exit(1)
    
    backup = history[backup_index - 1]
    restore_backup(backup)
    