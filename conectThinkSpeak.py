import serial
import time
import schedule
import urllib
from urllib.request import urlopen

    #call api thinkspeak
def update_data(a,b):
    #see the "api_key=0ZISHJU9RNPHEAIN" ? That's my api key from thinkspeak, if you want to connect to your thinkspeak, you should replace it with your api key
    data = urlopen('https://api.thingspeak.com/update?api_key=0ZISHJU9RNPHEAIN&field1='+str(a)+"&field2="+str(b))
    print('Updated data: ', data)

def main_func1():
    #create connect to COM 2, baud rate 9600
    arduino = serial.Serial('COM2',9600)
    print('Conected to Arduino')
    #get data from arduino
    arduino_data = arduino.readline()
    print(arduino_data)

    decoded_values = str(arduino_data[0:len(arduino_data)].decode("utf-8"))
    list_values = decoded_values.split('x')
    for item in list_values:
        list_in_floats.append(float(item))
    #a and b is temp and moist
    a = list_in_floats[0]
    b = list_in_floats[1]

    update_data(a,b)  
 
    print(f'Data from arduino: {list_in_floats}')

    arduino_data = 0
    list_in_floats.clear()
    list_values.clear()
    arduino.close()

#---------------------

list_values = []
list_in_floats=[]

print("Begin")

schedule.every(4).seconds.do(main_func1)

while 1:
    schedule.run_pending()
    time.sleep(1)