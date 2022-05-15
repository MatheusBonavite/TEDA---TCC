import matplotlib.pyplot as plt
import re

filename = "adjency_test_after.txt"
filehandle = open(filename, 'r')
x_vec = []
rad_vec = []
color_scheme = []

def value_for_color(value):
    if value == '0':
        return 'r'
    if value == '1':
        return 'b'
    if value == '2':
        return 'y'
    if value == '3':
        return 'g'
    if value == '4':
        return 'm'
    if int(value) >= 1000:
        return f"#71{value}"
    if int(value) >= 100:
        return f"#2b4{value}"
    if int(value) >= 10:
        return f"#8bc0{value}"
    return f"#1cdf1{value}"

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
        color_scheme.append(*[value_for_color(value) for value in col])

fig, ax = plt.subplots()
ax.set_xlim((0, 4.5))
ax.set_ylim((0, 4.5))
ax.grid()

while True:
    line = filehandle.readline()
    if not line:
        break
    first_coordinate = line.split(" ")[0]
    second_coordinate = line.split(" ")[1]
    ax.scatter((first_coordinate), (second_coordinate), color='#000000', s=(250./fig.dpi)**2)

for i in range(len(x_vec)):
    circles = plt.Circle((x_vec[i][0], x_vec[i][1]), rad_vec[i], color=color_scheme[i], fill=False)
    ax.add_patch(circles)

fig.savefig('plot_micro_clusters_3.png')
filehandle.close()