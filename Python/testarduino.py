import serial # pip install pyserial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0);

fig = plt.figure(figsize=(7,3));
plt.ion();
ax = fig.add_subplot()

fig.show()
x = []
i = 0
l = 200
ser.close()
ser.open()

for i in range(l):
	ser1 = ser.readline().decode('ascii')
	ser2 = ser.readline().decode('ascii')
	x.append(ser2)
	ax.plot(x, color ='g')
	fig.canvas.draw()
	ax.set_xlim(left=max(0, i-30), right=i+60)
	plt.pause(0.001)
plt.show()
