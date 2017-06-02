#!/usr/bin/env python

#Armur Bay

import serial, time

SERIALPORT = "/dev/ttyUSB0"
BAUDRATE = 9600

ser = serial.Serial(SERIALPORT, BAUDRATE)
ser.bytesize = serial.EIGHTBITS         #number of bits per bytes
ser.parity = serial.PARITY_NONE         #set parity check: no parity
ser.stopbits = serial.STOPBITS_ONE      #number of stop bits
#ser.timeout = None                     #block read
#ser.timeout = 0                        #non-block read
ser.timeout = None                      #timeout block read
ser.xonxoff = False                     #disable software flow control
ser.rtscts = False                      #disable hardware (RTS/CTS) flow control
ser.dsrdtr = False                      #disable hardware (DSR/DTR) flow control
ser.writeTimeout = 0                    #timeout for write

while True:
#print 'Starting Up Serial Monitor'

    if ser.isOpen():

        try:
            ser.flushInput()            #flush input buffer, discarding all its contents
            ser.flushOutput()           #flush output buffer, aborting current output

            ser.write("RB0\r\n")
            print("retrieve data: RB0")
            response = ser.readline()
            print(response)

            ser.write("RB1\r\n")
            print("retrieve data: RB1")
            response = ser.readline()
            print(response)

            ser.write("RB2\r\n")
            print("retrieve data: RB2")
            response = ser.readline()
            print(response)

            ser.write("RB3\r\n")
            print("retrieve data: RB3")
            response = ser.readline()
            print(response)

            ser.write("RB4\r\n")
            print("retrieve data: RB4")
            response = ser.readline()
            print(response)

            ser.write("RB5\r\n")
            print("retrieve data: RB5")
            response = ser.readline()
            print(response)

            ser.write("RB6\r\n")
            print("retrieve data: RB6")
            response = ser.readline()
            print(response)

            ser.write("RB7\r\n")
            print("retrieve data: RB7")
            response = ser.readline()
            print(response)
            
            ser.write("RB8\r\n")
            print("retrieve data: RB8")
            response = ser.readline()
            print(response)

            ser.write("RB9\r\n")
            print("retrieve data: RB9")
            response = ser.readline()
            print(response)

            time.sleep(0)
            numberOfLine = 0

            #ser.close()

        except Exception, e:
            print "error communicating...: " + str(e)
else:
    print "cannot open serial port "
