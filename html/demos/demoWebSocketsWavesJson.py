#!/usr/bin/python
from sys import stdout
from time import sleep
from json import dumps
import numpy as np
import struct

xmin = -100;
xmax = +100;
ymin = -100;
ymax = +100;
nx = 100;
ny = 30;
#############################################################
x = np.linspace(xmin, xmax, nx+1)
y = np.linspace(ymin, ymax, ny+1)
xx, yy = np.meshgrid(x, y, sparse = False)
#Z0 = np.cos(xx**2 + yy**2) / np.sqrt(xx**2 + yy**2+0.25)
Z0 = 0.01*(xx**2 + yy**2)
count = 0

#############################################################
base91_alphabet = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$',
	'%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=',
	'>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '"']

def base91Encode(bindata):
    ''' Encode a bytearray to a Base91 string '''
    b = 0
    n = 0
    out = ''
    for count in range(len(bindata)):
        byte = bindata[count:count+1]
        b |= struct.unpack('B', byte)[0] << n
        n += 8
        if n>13:
            v = b & 8191
            if v > 88:
                b >>= 13
                n -= 13
            else:
                v = b & 16383
                b >>= 14
                n -= 14
            out += base91_alphabet[v % 91] + base91_alphabet[v // 91]
    if n:
        out += base91_alphabet[b % 91]
        if n>7 or b>90:
            out += base91_alphabet[b // 91]
    return out

def convertToString(x):
    return base91Encode(np.float32(x).tostring())

while True:
    z = np.cos(2*np.pi*count/20.0)*Z0
    d = [{'type':'waves',\
          'nx':nx,\
          'ny':ny,\
          'xmin':xmin,\
          'xmax':xmax,\
          'ymin':ymin,\
          'ymax':ymax,\
          'z':convertToString(z)}]
    print(dumps(d))
    stdout.flush()
    sleep(1.0/20.0)
    #sleep(1.0)
    count+=1