import matplotlib.pyplot as plt
import re

filename = "adjency_test.txt"
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
ax.set_xlim((0, 1))
ax.set_ylim((0, 1))
for i in range(len(x_vec)):
    circles = plt.Circle((x_vec[i][0], x_vec[i][1]), rad_vec[i], color='r', fill=False)
    ax.add_patch(circles)

x0 = 0.33
x1 = 0.315
for _ in range(50000):
    x0 = 4.0 * (x0) * (1.0 - x0)
    x1 = 4.0 * (x1) * (1.0 - x1)
    ax.scatter((x0), (x1), color='y', s=(150./fig.dpi)**2)

fig.savefig('plot_micro_clusters.png')
filehandle.close()