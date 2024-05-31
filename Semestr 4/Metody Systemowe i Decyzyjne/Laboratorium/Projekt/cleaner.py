import pyodbc

SERVER_NAME = '(localdb)\\Local'
DATABASE_NAME = 'JobOffers'

CONNECTION_STRING = f"DRIVER={{ODBC Driver 17 for SQL Server}};SERVER={SERVER_NAME};DATABASE={DATABASE_NAME};Trusted_Connection=yes;"

conn = pyodbc.connect(CONNECTION_STRING)
cursor = conn.cursor()

cursor.execute("SELECT * FROM Offers")
data = cursor.fetchall()

for record in data:
    location_name = record[7].split(",")[0].strip()
    cmd = f"UPDATE Offers SET Location = '{location_name}' WHERE Id = {record[0]}"
    print(cmd)
    cursor.execute(cmd)