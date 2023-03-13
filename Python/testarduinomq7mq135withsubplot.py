# https://toptechboy.com/python-with-arduino-lesson-11-plotting-and-graphing-live-data-from-arduino-with-matplotlib/
# https://www.youtube.com/watch?v=5D9mwqWBgCw

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
    plt.subplot(2,1,1)
    plt.ylim(200,1000)                              
    plt.title('MQ7 and MQ135 Live Streaming Sensor Data')     
    plt.grid(True)                                      
    plt.plot(PPMCO2, 'ro-', label='CO2 (from MQ135)')    
    plt.legend(loc='upper left')                    
                                 
    plt.subplot(2,1,2)
    plt.ylim(100,1000)                     
    plt.grid(True)  
    plt.plot(MQ7CO, 'b^-', label='CO (from MQ7)')                  
    plt.ticklabel_format(useOffset=False)         
    plt.legend(loc='upper right')                 

while True: 
    while (arduinoData.inWaiting()==0): 
        pass 
    arduinoString = arduinoData.readline()
    # print(arduinoString)	
    s = str(arduinoString)
    s = s.replace('b\'','')
    s = s.replace('\\r\\n\'','')
    # print(s) 	 
    dataArray = s.split(',')
    co2 = float(dataArray[0])            
    co = float(dataArray[1])  
    PPMCO2.append(co2)            
    MQ7CO.append(co)                
    drawnow(makeFig)                      
    plt.pause(.000001)                    
    cnt=cnt+1
    
if(cnt>50):
	PPMCO2.pop(0)
	MQ7CO.pop(0)
	