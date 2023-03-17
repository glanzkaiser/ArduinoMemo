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
    fig, axs = plt.subplots(2,2)
    (ax1, ax2), (ax3, ax4) = axs                            
    ax1.grid(True)                                      
    ax1.plot(PPMCO2, 'ro-', label='CO2 (from MQ135)')    
    ax1.legend(loc='upper left')                    
                                                 
    ax2.grid(True)  
    ax2.plot(MQ7CO, 'g*-', label='CO (from MQ7)')                  
    ax2.ticklabel_format(useOffset=False)         
    ax2.legend(loc='upper right')       
          
    ax3.grid(True)  
    ax3.plot(tempC, 'mp-', label='Degrees C')                  
    ax3.ticklabel_format(useOffset=False)         
    ax3.legend(loc='upper right') 

    ax4.grid(True)  
    ax4.plot(altitude, 'kD-', label='Altitude (m)')                  
    ax4.ticklabel_format(useOffset=False)         
    ax4.legend(loc='upper right') 

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