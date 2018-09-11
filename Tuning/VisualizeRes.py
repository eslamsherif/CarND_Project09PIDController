import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

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
speed = []

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
        elif line[0] == "S":
            speed.append(float(line[ParseThres:]))

file.close()

fig, (ax1,ax2, ax3) = plt.subplots(3, 1, figsize=(8, 8))
# ax1.plot(cte    , 'm')
# ax1.plot(p_error, 'y')
# ax1.plot(i_error, 'w')
# ax1.plot(d_error, 'k')
ax1.plot(PTerm  , 'b')
PTerm_L = mpatches.Patch(color='b', label='PTerm')
ax1.plot(ITerm  , 'g')
ITerm_L = mpatches.Patch(color='g', label='ITerm')
ax1.plot(DTerm  , 'r--')
DTerm_L = mpatches.Patch(color='r', label='DTerm')
ax2.plot(toterr , 'r')
ax3.plot(speed , 'b')
ax1.set_title('PID Terms visualization')
ax2.set_title('PID Total Error visualization')
ax3.set_title('Vehicle Speed')
ax1.legend(handles=[PTerm_L, ITerm_L, DTerm_L])

plt.show()