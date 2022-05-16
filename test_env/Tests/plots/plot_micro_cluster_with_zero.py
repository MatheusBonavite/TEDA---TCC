import matplotlib.pyplot as plt
import re

filename = "adjency_test_after.txt"
filehandle = open(filename, 'r')
filename2 = "samples.txt"
filehandle2 = open(filename2, 'r')

fig, ax = plt.subplots()
ax.set_xlim((0, 3))
ax.set_ylim((1, 3))
ax.grid()

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
    line2 = filehandle2.readline()

    if not line and not line2:
        break

    if line2:
        first_coordinate = line2.split(" ")[0]
        second_coordinate = line2.split(" ")[1]
        ax.scatter((float(first_coordinate)), (float(second_coordinate)), color='k', s=(120./fig.dpi)**2, zorder=0)
    
    if line:
        x = re.findall("(?<=\{)[0-9.]*(?=\})", line)
        rad = re.findall("(?<=\()[0-9.]*(?=\))", line)
        col = re.findall("(?<=\[)[0-9.]*(?=\])", line)
        if x and rad and col:
            circles = plt.Circle((float(x[0]), float(x[1])), float(rad[0]), color=value_for_color(col[0]), fill=False, zorder=1)
            ax.add_patch(circles)


fig.savefig('plot_micro_clusters_after.png')
filehandle.close()
filehandle2.close()