import matplotlib.pyplot as plt
import re

def value_for_color(value):
    if value == '0':
        return 'b'
    if value == '1':
        return 'g'
    if value == '2':
        return 'r'
    if value == '3':
        return 'c'
    if value == '4':
        return 'm'
    if value == '5':
        return 'y'
    if value == '6':
        return 'k'
    if value == '7':
        return 'pink'
    if value == '8':
        return 'darkcyan'
    if value == '9':
        return '#451f55'
    if value == '10':
        return '#22162b'
    if value == '11':
        return '#724e91'
    return 'darkgreen'

fig, ax = plt.subplots()
ax.set_xlim((-7, 2))
ax.set_ylim((49, 59))

filename = "answer3.txt"
filehandle = open(filename, 'r')
x_vec = []
rad_vec = []
i=0
while True:
    line = filehandle.readline()
    if not line:
        break
    x = re.findall("(?<=\{)-[0-9.]*(?=\})|(?<=\{)[0-9.]*(?=\})", line)
    rad = re.findall("(?<=\()[0-9.]*(?=\))", line)
    col = re.findall("(?<=\[)[0-9.]*(?=\])", line)

    circles = plt.Circle((float(x[0]), float(x[1])), float(rad[0])/10, color=value_for_color(col[0]), fill=False)
    ax.add_patch(circles)

ax.grid()

# filename = "samples.txt"
# filehandle = open(filename, 'r')
# while True:
#     line = filehandle.readline()
#     if not line:
#         break
#     first_coordinate = line.split(',')[0]
#     second_coordinate = line.split(',')[1]
#     ax.scatter((first_coordinate), (second_coordinate), color='y', s=(10./fig.dpi))

fig.savefig('plot_micro_clusters_3.png')
filehandle.close()