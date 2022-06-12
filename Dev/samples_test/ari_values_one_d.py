import pandas as pd
from sklearn.metrics import adjusted_rand_score
import matplotlib.pyplot as plt
import plotly.graph_objects as go
import numpy as np

stream_df = pd.read_csv("std4_csv.csv", header=0, sep=",")
y = stream_df['class'].values
variance_limit = 0.0001
the_value = 0
x_v = []
y_v = []
adjusted_r = []

fig, ax = plt.subplots()
while variance_limit < 0.0030:
    Y = []
    filename = f"./classified_samples{the_value}.txt"
    filehandle = open(filename, 'r')
    while True:
        line = filehandle.readline()
        if not line:
            break
        third_coordinate = line.split(' ')[0]
        Y.append(third_coordinate)
        first_coordinate = line.split(' ')[1]
        second_coordinate = line.split(' ')[2].replace('\n', '')
    adjusted_score = adjusted_rand_score(y, Y)
    y_v.append(variance_limit)
    adjusted_r.append(adjusted_score)
    variance_limit += 0.0001
    the_value += 1

ax.plot(y_v, adjusted_r, 'o--', color='grey', alpha=0.3)
print(max(adjusted_r))
fig.savefig('std_4_one_d.png')