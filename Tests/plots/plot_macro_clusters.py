import matplotlib.pyplot as plt
import re

def value_for_color(value):
    if(int(value) == 0):
        return 'b'
    if(int(value) == 7):
        return 'r'
    if(int(value) >= 1000):
        return f"#24{value}"
    if(int(value) >= 100):
        return f"#381{value}"
    if(int(value) >= 10):
        return f"#578C{value}"
    return f"#A262D{value}"

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