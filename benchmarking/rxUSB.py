#!/usr/bin/env python

############################### rxUSB.py ###############################

import serial;
import time;

def wait_for_data(serial): 
    while serial.read() != 'S':
        pass
    return

def main():
    try:
        serialPort = serial.Serial("/dev/ttyACM0",\
                                   115200,
                                   serial.EIGHTBITS,\
                                   serial.PARITY_NONE,
                                   serial.STOPBITS_ONE);
    except:
        print("Couldn't open serial port");
        exit();

    packet_Length = 160
    num_Packets = 1000; 
    byteSent = 0;   

    f = open('log','a');
    # First time slice
    t1 = time.time();
    # serialPort.write('T');

    # Reads packets recieved
    for i in range(num_Packets):
        #wait_for_data(serialPort)
	serialPort.write('T')
        read = serialPort.read(packet_Length);
	#start = read.index('S')
	#read = read[start:start+160]
        byteSent += len(read);

    # Second time slice 
    t2 = time.time()
    print "READ: %s\n" % read
    throughPut = (byteSent)/(t2-t1);

    # Write to File
    intToString = ('Time:', t2-t1);
    s = str(intToString);
    f.write(s);

    intToString = ('KB/s:', throughPut);
    s = str(intToString);
    f.write(s);

    intToString = ('Bytes Recieved:', byteSent);
    s = str(intToString);
    f.write(s);

    # Print to console
    print (t2 -t1);  
    print ("%d Bytes/s %0.2f MBytes/s %d Packages" % (throughPut, throughPut/1024/1024, throughPut/160));
    print ("Test Done: Recieved a total of %d bytes" % byteSent);
    f.write("\n");
    f.closed;

if __name__ == '__main__':
    main()
