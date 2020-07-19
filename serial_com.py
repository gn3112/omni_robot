import serial
import time

ser = serial.Serial('/dev/cu.usbmodem14101', 9600)
# time.sleep(3)
count = 0
while count < 25:
    ser.write(b'0')
    count += 1
    time.sleep(0.5)
    ser.write(b'1')
