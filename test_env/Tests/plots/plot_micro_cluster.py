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
ax.set_xlim((-2, 2))
ax.set_ylim((-2, 2))

x0 = 0.33
x1 = 0.315
for _ in range(30000):
    first_coordinate = x0
    x0 = 4.0 * (x0) * (1.0 - x0)
    second_coordinate = x0
    ax.scatter((first_coordinate), (second_coordinate), color='y', s=(150./fig.dpi)**2)

for i in range(len(x_vec)):
    circles = plt.Circle((x_vec[i][0], x_vec[i][1]), rad_vec[i], color='r', fill=False)
    ax.add_patch(circles)

fig.savefig('plot_micro_clusters.png')
filehandle.close()