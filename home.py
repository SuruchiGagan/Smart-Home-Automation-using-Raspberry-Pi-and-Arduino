import RPi.GPIO as GPIO
import time
import urllib2

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

GPIO.setup(3,GPIO.OUT)
GPIO.output(3,GPIO.LOW)
i=0
j=0
while True:
 try: 
	f = urllib2.urlopen('http://192.168.0.100/software/value.txt')
	
	st = int(f.read())
	if (st == 0):
		if(i==0):
			GPIO.output(3,GPIO.LOW)
			print('Off')
			i=1;
			j=0;
			
	elif (st == 1):
		if(j==0):
			GPIO.output(3,GPIO.HIGH)
			print ('on')
			j=1
			i=0

 except KeyboardInterrupt:
	GPIO.cleanup(3)
	exit()
