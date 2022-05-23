import matplotlib.pyplot as plt
import re

def value_for_color(value):
    if value == '0':
        return 'darkgreen'
    if value == '1':
        return 'k'
    if value == '2':
        return 'orange'
    if value == '3':
        return 'r'
    if value == '4':
        return 'b'
    if value == '5':
        return 'g'
    if value == '6':
        return 'y'
    if value == '7':
        return 'm'
    if value == '8':
        return 'lightblue'
    if value == '9':
        return 'coral'
    return 'y'

fig, ax = plt.subplots()
ax.set_xlim((-250, 250))
ax.set_ylim((0, 600))

filename = "damian_lillard.txt"
filehandle = open(filename, 'r')
i=0
ax.grid()

while True:
    line = filehandle.readline()
    if not line:
        break
    col = re.findall("(?<=\[)[0-9.]*(?=\])", line)
    x = re.findall("(?<=\()[0-9.]*(?=\))|(?<=\()-[0-9.]*(?=\))", line)
    ax.scatter(float(x[0]), float(x[1]), color=value_for_color(col[0]), s=(120./fig.dpi)**2)
    
fig.savefig('./damian_lillard.png')
filehandle.close()