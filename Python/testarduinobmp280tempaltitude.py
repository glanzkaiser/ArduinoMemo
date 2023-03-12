# https://toptechboy.com/python-with-arduino-lesson-11-plotting-and-graphing-live-data-from-arduino-with-matplotlib/
# https://python-forum.io/thread-32161.html

import serial 
import numpy  
import matplotlib.pyplot as plt
from drawnow import *

tempC= []
altitude=[]

arduinoData = serial.Serial('/dev/ttyACM0', 115200) 
plt.ion()
cnt=0

def makeFig(): 
    plt.ylim(20,35)
    plt.title('BMP280 Live Streaming Sensor Data')   
    plt.grid(True) 
    plt.ylabel('Temp C')                            
    plt.plot(tempC, 'ro-', label='Degrees C')       
    plt.legend(loc='upper left')                    
    plt2=plt.twinx()                                
    plt.ylim(600,2000)                           
    plt2.plot(altitude, 'b^-', label='Altitude (m)')
    plt2.set_ylabel('Altitude (m)')                 
    plt2.ticklabel_format(useOffset=False)          
    plt2.legend(loc='upper right')                  

while True: 
    while (arduinoData.inWaiting()==0): 
        pass 
    arduinoString = arduinoData.readline().decode('ascii') 
    dataArray = arduinoString.split(',')  
    # the usage of String class is not preferred (memory problems)
    temp = float(dataArray[0])            
    alt = float(dataArray[1])   	  
    tempC.append(temp)                    
    altitude.append(alt)                  
    drawnow(makeFig)                      
    plt.pause(.000001)                    
    cnt=cnt+1

if(cnt>50):
	tempC.pop(0)
	altitude.pop(0)