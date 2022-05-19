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
ax.set_xlim((0, 3))
ax.set_ylim((1, 3))

filename = "file_macro_after.txt"
filehandle = open(filename, 'r')
x_vec = []
rad_vec = []
i=0

ax.grid()

filename2 = "./samples.txt"
filehandle2 = open(filename2, 'r')
while True:
    line2 = filehandle2.readline()
    if not line2:
        break
    first_coordinate = line2.split(' ')[0]
    second_coordinate = line2.split(' ')[1].replace('\n', '')
    ax.scatter(float(first_coordinate), float(second_coordinate), color='y', s=(120./fig.dpi))

while True:
    line = filehandle.readline()
    if not line:
        break
    x = re.findall("(?<=\{)-[0-9.]*(?=\})|(?<=\{)[0-9.]*(?=\})", line)
    rad = re.findall("(?<=\()[0-9.]*(?=\))", line)
    col = re.findall("(?<=\[)[0-9.]*(?=\])", line)

    circles = plt.Circle((float(x[0]), float(x[1])), float(rad[0]), color=value_for_color(col[0]), fill=False)
    ax.add_patch(circles)
    
fig.savefig('plot_macro_clusters_after.png')
filehandle.close()
filehandle2.close()