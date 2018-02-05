import paramiko
import mysql.connector
from mysql.connector import errorcode
import socket

client = paramiko.SSHClient()
client.load_system_host_keys()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect(hostname = 'lab301.asuscomm.com', port = 1128, username = 'pi', password = 'raspberry')
stdin, stdout, stderr = client.exec_command('ls -l')

print('wildcat5566')

config = {
   'user': 'root',
   'password': 'wildcat5566',
   'host': '192.168.1.129',
   'port': 3306,
   'database': 'test_160618',
      }
cnx = mysql.connector.connect(**config)
cursor = cnx.cursor()

print('slow and steady')

def add_table(cursor):
   try:
        cursor.execute('DROP TABLE IF EXISTS `write_160627`')
        cursor.execute('''CREATE TABLE write_160627 (
        ID INT PRIMARY KEY NOT NULL,
        Temperature INT,
        Humidity INT,
        CO2 INT,
        Light INT)''')
   except Error: #as err:
        print('Gg')

try:
    add_table(cursor)
except Error:# as err:
    print('errrr')

add_read = ("INSERT INTO write_160627"
            "(ID, Temperature)"
            "VALUES (%s, %s)")
data_read = (1, 28)
   
    
#while 1 :
 
    #text = ser.readline().decode('utf-8')
    #list1 = text.split(",")
    #print(list1)

    #count = list1[0]
    #rh = list1[1]
    #tem = list1[2]
    #co2 = list1[3]
    #light = list1[4]
    #add_read = ("INSERT INTO write_160605 "
    #           "(ID, Temperature, Humidity, CO2, Light) "
    #           "VALUES (%s, %s, %s, %s, %s)")
    #data_read = (count, tem, rh, co2, light)

cursor.execute(add_read, data_read)
cnx.commit() 
    
    
cursor.close()
cnx.close()
