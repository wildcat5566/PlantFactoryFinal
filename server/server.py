from __future__ import print_function
import pymysql
from pymysql import Error

### Mysql connector code for SERVER side. ###

import serial
ser = serial.Serial('/dev/ttyACM0', 9600)

config = {
    'user': 'root',
    'password': 'wildcat5566',
    'host': '192.168.1.129', #129 is the local IP of SERVER side.
    'database': 'PlantFactoryTest',
    }
cnx = pymysql.connect(**config)
cursor = cnx.cursor()

count = 0

def add_table(cursor):
   try:
        # generate target table for the client side.
        cursor.execute('DROP TABLE IF EXISTS `target`')
        cursor.execute('''CREATE TABLE target (
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
    
while 1 :
 
    text = ser.readline().decode('utf-8')
    list1 = text.split(",")
    print(list1)

    count = list1[0]
    rh = list1[1]
    tem = list1[2]
    co2 = list1[3]
    light = list1[4]
    add_read = ("INSERT INTO target "
               "(ID, Temperature, Humidity, CO2, Light) "
               "VALUES (%s, %s, %s, %s, %s)")
    data_read = (count, tem, rh, co2, light)
    cursor.execute(add_read, data_read)

    cnx.commit()
    
    
cursor.close()
cnx.close()
