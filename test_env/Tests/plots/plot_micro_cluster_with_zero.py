import matplotlib.pyplot as plt
import re

filename = "adjency_test.txt"
filehandle = open(filename, 'r')
x_vec = []
rad_vec = []
color_scheme = []

while True:
    line = filehandle.readline()
    if not line:
        break
    x = re.findall("(?<=\{)[0-9.]*(?=\})", line)
    rad = re.findall("(?<=\()[0-9.]*(?=\))", line)
    col = re.findall("(?<=\[)[0-9.]*(?=\])", line)
    if x:
        x_vec.append([float(value) for value in x])
    if rad:
        rad_vec.append(*[float(value) for value in rad])
    if col:
        color_scheme.append(*['b' if value == '10' else 'g' if value == '9' else 'r' for value in col])

fig, ax = plt.subplots()
ax.set_xlim((0, 4.5))
ax.set_ylim((0, 4.5))
ax.grid()

x0 = 0.33
x1 = 0.315
for i in range(100):
    centers = []
    if i >= 0 and i < 50:
        centers = [3.0, 2.0]
    if i >= 50:       
        centers = [0.5, 2.0]
        
    x0 = 4.0 * (x0) * (1.0 - x0)
    x1 = 4.0 * (x1) * (1.0 - x1)
    first_coordinate = centers[0] + x0
    second_coordinate = centers[1] + x1
    ax.scatter((first_coordinate), (second_coordinate), color='y', s=(150./fig.dpi)**2)

for i in range(len(x_vec)):
    print(color_scheme[i])
    if color_scheme[i] == 'r' :
        circles = plt.Circle((x_vec[i][0], x_vec[i][1]), rad_vec[i], color='r', fill=False)
    else:
        circles = plt.Circle((x_vec[i][0], x_vec[i][1]), rad_vec[i], color=color_scheme[i], fill=False)
    ax.add_patch(circles)

fig.savefig('plot_micro_clusters_2.png')
filehandle.close()