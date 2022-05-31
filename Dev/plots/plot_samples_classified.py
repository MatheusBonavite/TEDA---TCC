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
ax.set_xlim((0, 1))
ax.set_ylim((0, 1))

filename = "./classified_samples.txt"
filehandle = open(filename, 'r')
while True:
    line = filehandle.readline()
    if not line:
        break
    third_coordinate = line.split(' ')[0]
    first_coordinate = line.split(' ')[1]
    second_coordinate = line.split(' ')[2].replace('\n', '')
    print(first_coordinate, second_coordinate, third_coordinate)
    ax.scatter(float(first_coordinate), float(second_coordinate), color=value_for_color(third_coordinate), s=(120./fig.dpi))
    
fig.savefig('classified_samples.png')
filehandle.close()