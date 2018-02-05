from __future__ import print_function
import pymysql
from pymysql import Error

import serial
ser = serial.Serial('/dev/ttyACM0', 9600)

config = {
    'user': 'root',
    'password': 'wildcat5566',
    'host': '192.168.1.129',
    'database': 'PlantFactoryTest',
    }
# 187 = my machine (CLIENT)
# Tasks:
#   s = 0, Read count from Arduino
#   s = 0, Read target from my database
#   s = 55, Save record to my database

# 129 = your machine (SERVER)
# Tasks:
#   s = 0, Send reference inputs to my database

cnx = pymysql.connect(**config)
cursor = cnx.cursor()

count = 0

def add_table(cursor):
   try:
        cursor.execute('DROP TABLE IF EXISTS `sample`')
        cursor.execute('''CREATE TABLE sample (
        ID INT PRIMARY KEY NOT NULL,
        Temperature DOUBLE,
        Humidity DOUBLE,
        CO2 INT)''')
   except Error: #as err:
        print('Gg')

try:
    add_table(cursor)
except Error:# as err:
    print('errrr')

while 1 :
    # s%60 == 0, minute count
    count = ser.readline().decode('utf-8')
    print(count)

    # s%60 == 0, retrieve targets
    query = ("SELECT ID, Temperature, Humidity, CO2, Light FROM target "
             "WHERE ID BETWEEN %s AND %s") %(count, count)
    cursor.execute(query)
    for (ID, Temperature, Humidity, CO2, Light) in cursor:
        rhTarget = str(Humidity)
        temTarget = str(Temperature)
        co2Target = str(CO2)
        lightTarget = str(Light)
        print(rhTarget.encode('utf-8') + temTarget.encode('utf-8') + co2Target.encode('utf-8') + lightTarget.encode('utf-8'))
        ser.write(rhTarget.encode('utf-8') + temTarget.encode('utf-8') + co2Target.encode('utf-8') + lightTarget.encode('utf-8'))

    # s%60 == 55, make sample
    text = ser.readline().decode('utf-8')
    list1 = text.split(",")
    print(list1)
    
    rh = list1[0]
    tem = list1[1]
    co2 = list1[2]

    # save sample data into database
    add_read = ("INSERT INTO sample "
               "(ID, Temperature, Humidity, CO2) "
               "VALUES (%s, %s, %s, %s)")
    data_read = (count, tem, rh, co2)
    cursor.execute(add_read, data_read)

    cnx.commit()
    
    
cursor.close()
cnx.close()
