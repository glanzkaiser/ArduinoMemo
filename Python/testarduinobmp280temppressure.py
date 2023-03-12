# https://toptechboy.com/python-with-arduino-lesson-11-plotting-and-graphing-live-data-from-arduino-with-matplotlib/
# https://python-forum.io/thread-32161.html

import serial # import Serial Library
import numpy  # Import numpy
import matplotlib.pyplot as plt #import matplotlib library
from drawnow import *

tempC= []
pressure=[]

arduinoData = serial.Serial('/dev/ttyACM0', 115200) #Creating our serial object named arduinoData
plt.ion() #Tell matplotlib you want interactive mode to plot live data
cnt=0

def makeFig(): #Create a function that makes our desired plot
    plt.ylim(26,30)                                 #Set y min and max values
    plt.title('BMP280 Live Streaming Sensor Data')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Temp C')                            #Set ylabels
    plt.plot(tempC, 'ro-', label='Degrees C')       #plot the temperature
    plt.legend(loc='upper left')                    #plot the legend
    plt2=plt.twinx()                                #Create a second y axis
    plt.ylim(850,995)                           #Set limits of second y axis- adjust to readings you are getting
    plt2.plot(pressure, 'b^-', label='Pressure (hPa)') #plot pressure data
    plt2.set_ylabel('Pressure (hPa)')                    #label second y axis
    plt2.ticklabel_format(useOffset=False)           #Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='upper right')                  #plot the legend

while True: # While loop that loops forever
    while (arduinoData.inWaiting()==0): #Wait here until there is data
        pass #do nothing
    arduinoString = arduinoData.readline().decode('ascii') #read the line of text from the serial port
    # print(arduinoString)	 	   # check the output 
    dataArray = arduinoString.split(',')   #Split it into an array called dataArray
    # the usage of String class is not preferred (memory problems)
    temp = float( dataArray[0])            #Convert first element to floating number and put in temp
    P = float( dataArray[1])               #Convert second element to floating number and put in P
    tempC.append(temp)                     #Build our tempC array by appending temp readings
    pressure.append(P)                     #Building our pressure array by appending P readings
    drawnow(makeFig)                       #Call drawnow to update our live graph
    plt.pause(.000001)                     #Pause Briefly. Important to keep drawnow from crashing
    cnt=cnt+1
    #If you have 50 or more points, delete the first one from the array
if(cnt>50):
	tempC.pop(0)#This allows us to just see the last 50 data points
	pressure.pop(0)
