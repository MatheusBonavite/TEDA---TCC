import matplotlib.pyplot as plt
import random
import re
color_index = []
color_value = {}

def value_for_color(value):
    hexadecimal = ["#"+''.join([random.choice('ABCDEF0123456789') for i in range(6)])]
    if(int(value) in color_index):
        return color_value[value]
    else:
        color_value[value] = hexadecimal[0]
        color_index.append(int(value))
        return hexadecimal[0]

fig, ax = plt.subplots()
ax.set_xlim((0, 2000))
ax.set_ylim((1, 4))


ax.grid()

filename = "./empirical_m.txt"
filehandle = open(filename, 'r')
line_number = 0
while True:
    line = filehandle.readline()
    if not line:
        break
    value = line.split(' ')[0].replace('\n', '')
    print(line_number, value)
    ax.scatter(line_number, float(value), s=(120./fig.dpi)**2, color='r')
    line_number += 15

fig.savefig('empirical_m_discrete.png')
filehandle.close()