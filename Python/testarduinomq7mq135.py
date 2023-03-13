# https://toptechboy.com/python-with-arduino-lesson-11-plotting-and-graphing-live-data-from-arduino-with-matplotlib/
# https://python-forum.io/thread-32161.html

import serial 
import numpy  
import matplotlib.pyplot as plt 
from drawnow import *

PPMCO2=[]
MQ7CO= []

arduinoData = serial.Serial('/dev/ttyACM0', 115200) 
plt.ion() 
cnt=0

def makeFig(): 
    plt.ylim(200,1000)                              
    plt.title('MQ135 Live Streaming Sensor Data')     
    plt.grid(True)                               
    plt.ylabel('CO2 (ppm)')                            
    plt.plot(PPMCO2, 'ro-', label='CO2 (from MQ135)')    
    plt.legend(loc='upper left')                    
    plt2=plt.twinx()                                
    plt.ylim(300,1000)                          
    plt2.plot(MQ7CO, 'b^-', label='CO (from MQ7)')
    plt2.set_ylabel('CO (ppm)')                    
    plt2.ticklabel_format(useOffset=False)         
    plt2.legend(loc='upper right')                 

while True: 
    while (arduinoData.inWaiting()==0): 
        pass 
    arduinoString = arduinoData.readline().decode('ascii')
    # print(arduinoString)	 	 
    dataArray = arduinoString.split(',')
    co2 = float( dataArray[0])            
    co = float( dataArray[1])  
    PPMCO2.append(co2)            
    MQ7CO.append(co)                
    drawnow(makeFig)                      
    plt.pause(.000001)                    
    cnt=cnt+1
    
if(cnt>50):
	PPMCO2.pop(0)
	MQ7CO.pop(0)
	