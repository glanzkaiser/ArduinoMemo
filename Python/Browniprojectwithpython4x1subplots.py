# https://toptechboy.com/python-with-arduino-lesson-11-plotting-and-graphing-live-data-from-arduino-with-matplotlib/
# https://www.youtube.com/watch?v=5D9mwqWBgCw
# https://java2blog.com/python-write-array-to-csv/
# https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.axes.Axes.plot.html
import serial 
import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt 
from drawnow import *

tempC=[]
altitude=[]
PPMCO2=[]
MQ7CO=[]

arduinoData = serial.Serial('/dev/ttyACM0', 115200) 
plt.ion() 
cnt=0

def makeFig(): 
    fig, axs = plt.subplots(4, sharex=True)
    fig.suptitle('Browni Project')
    axs[0].plot(PPMCO2, 'ro-', label='CO2')  
    axs[0].legend(loc='upper left')                                                 
    axs[1].plot(MQ7CO, 'g*-', label='CO')
    axs[1].legend(loc='upper left')                       
    axs[2].plot(tempC, 'mp-', label='Degrees C')                  
    axs[2].legend(loc='upper left')
    axs[3].plot(altitude, 'kD-', label='Altitude (m)')                  
    axs[3].legend(loc='upper left')
while True: 
    while (arduinoData.inWaiting()==0): 
        pass 
    arduinoString = arduinoData.readline()
    #print(arduinoString)	
    s = str(arduinoString)
    s = s.replace('b\'','')
    s = s.replace('\\r\\n\'','')
    f = str(arduinoString)
    f = f.replace('b\'','[')
    f = f.replace('\\r\\n\'','],')
    print(s) 
    print(f)	 
    dataArray = s.split(',')
    temp = float(dataArray[0])            
    alt = float(dataArray[1])  
    co2 = float(dataArray[2])            
    co = float(dataArray[3]) 
    tempC.append(temp)            
    altitude.append(alt)                
    PPMCO2.append(co2)            
    MQ7CO.append(co)                
    drawnow(makeFig)                      
    plt.pause(.000001)     
    cnt=cnt+1
    
if(cnt>50):
	tempC.pop(0)
	altitude.pop(0)
	PPMCO2.pop(0)
	MQ7CO.pop(0)
#arr = np.asarray([f])
#pd.DataFrame(arr).to_csv('sample.csv', index_label = 'Index')	