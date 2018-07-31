import sys
import numpy as np
import matplotlib.pyplot as plt

## TODO: Some consistency checks on the input files would be nice
InFile = sys.argv[1]

file = open(InFile,"r")

Dlines = file.read()
lines = Dlines.splitlines()

cte = []
p_error = []
i_error = []
d_error = []
PTerm = []
ITerm = []
DTerm = []
toterr = []

ParseThres = 14

for line in lines:
    if ( line == "Listening to port 4567" ) or (line == "Connected!!!"):
        continue
    else:
        if line[0] == "C":
            cte.append(float(line[ParseThres:]))
        elif line[0] == "p":
            p_error.append(float(line[ParseThres:]))
        elif line[0] == "i":
            i_error.append(float(line[ParseThres:]))
        elif line[0] == "d":
            d_error.append(float(line[ParseThres:]))
        elif line[0] == "P":
            PTerm.append(float(line[ParseThres:]))
        elif line[0] == "I":
            ITerm.append(float(line[ParseThres:]))
        elif line[0] == "D":
            DTerm.append(float(line[ParseThres:]))
        elif line[0] == "T":
            toterr.append(float(line[ParseThres:]))

file.close()

fig, (ax1) = plt.subplots(1, 1, figsize=(8, 8))
ax1.plot(cte    , 'b')
ax1.plot(p_error, 'g')
ax1.plot(i_error, 'r')
ax1.plot(d_error, 'c')
ax1.plot(PTerm  , 'm')
ax1.plot(ITerm  , 'y')
ax1.plot(DTerm  , 'k')
ax1.plot(toterr , 'w')
ax1.set_title('PID Visualization')

plt.show()