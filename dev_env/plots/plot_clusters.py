import matplotlib.pyplot as plt
import re

def value_for_color(value):
    if(int(value) >= 100):
        return f"#451{value}"
    if(int(value) >= 10):
        return f"#4510{value}"
    return f"#45100{value}"

fig, ax = plt.subplots()
ax.set_xlim((-7, 2))
ax.set_ylim((49, 59))

filename = "answer4.txt"
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

    circles = plt.Circle((float(x[0]), float(x[1])), float(rad[0]), color=value_for_color(col[0]), fill=False)
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

fig.savefig('plot_micro_clusters_4.png')
filehandle.close()