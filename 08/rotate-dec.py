import sys
import math
import struct

if len(sys.argv) != 3:
    print 'python rotate-dec.py FILENAME KEY'
    sys.exit(1)

filename = sys.argv[1]
KEY = math.radians(-1 * float(sys.argv[2]))

enc = open(filename, 'rb').read()
dec = open(filename + '.dec', 'wb')

p = lambda x: struct.pack('b', x)
u = lambda x: struct.unpack('f', x)[0]

for i in range(0, len(enc), 8):
    x, y = u(enc[i:i+4]), u(enc[i+4:i+8])
    x_ = x * math.cos(KEY) - y * math.sin(KEY)
    y_ = x * math.sin(KEY) + y * math.cos(KEY)
    dec.write(p(round(x_)))
    dec.write(p(round(y_)))
