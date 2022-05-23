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
ax.set_xlim((-1, 1))
ax.set_ylim((0, 1))

filename = "damian_lilliard_macro.txt"
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
    first_coordinate = line2.split(',')[0]
    second_coordinate = line2.split(',')[1].replace('\n', '')
    ax.scatter(float(first_coordinate)/236.0, float(second_coordinate)/594.0, color='y', s=(120./fig.dpi))

while True:
    line = filehandle.readline()
    if not line:
        break
    x = re.findall("(?<=\{)-[0-9.]*(?=\})|(?<=\{)[0-9.]*(?=\})", line)
    rad = re.findall("(?<=\()[0-9.]*(?=\))", line)
    col = re.findall("(?<=\[)[0-9.]*(?=\])", line)

    circles = plt.Circle((float(x[0]), float(x[1])), float(rad[0]), color=value_for_color(col[0]), fill=False)
    ax.add_patch(circles)
    
fig.savefig('plot_macro_clusters_lillian.png')
filehandle.close()
filehandle2.close()