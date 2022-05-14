import matplotlib.pyplot as plt
import re

filename = "micro_clusters.txt"
filehandle = open(filename, 'r')
x_vec = []
rad_vec = []

while True:
    line = filehandle.readline()
    if not line:
        break
    x = re.findall("(?<=\{)[0-9.]*(?=\})", line)
    rad = re.findall("(?<=\()[0-9.]*(?=\))", line)
    if x:
        x_vec.append([float(value) for value in x])
    if rad:
        rad_vec.append(*[float(value) for value in rad])

fig, ax = plt.subplots()
ax.set_xlim((20.15, 20.25))
ax.set_ylim((2.9, 3.1))
ax.grid()

plot_l = [[20.2, 3.0],[20.18, 3.035], [20.19, 3.01],[20.18, 3.03],[15.0, 3.0],[15.01, 3.0],[20.18, 3.025],[20.18, 3.04],[16.0, 3.5],[16.5, 3.45]]

for i in range(len(x_vec)):
    circles = plt.Circle((x_vec[i][0], x_vec[i][1]), rad_vec[i], color='r', fill=False)
    ax.add_patch(circles)

for val in plot_l:
    first_coordinate = val[0]
    second_coordinate = val[1]
    ax.scatter((first_coordinate), (second_coordinate), color='y', s=(250./fig.dpi)**2)

fig.savefig('plot_micro.png')
filehandle.close()