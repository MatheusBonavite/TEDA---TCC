import pandas as pd
from sklearn.metrics import adjusted_rand_score
import plotly.graph_objects as go
import plotly.express as px
import pandas as pd

stream_df = pd.read_csv("std_2.csv", header=0, sep=",")
y = stream_df['class'].values
decay_value = 1000
variance_limit = 0.0
the_value = 0
x_v = []
y_v = []
adjusted_r = []

while decay_value < 4100:
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
        x_v.append(decay_value)
        y_v.append(variance_limit)
        adjusted_r.append(adjusted_score)
        variance_limit += 0.0001
        the_value += 1
    variance_limit = 0.0
    decay_value += 100

d = {'Decaimento':x_v,'Variância Limite':y_v, 'ARI': adjusted_r}
df = pd.DataFrame(d)
fig = px.scatter_3d(df, x='Decaimento', y='Variância Limite', z='ARI',
                    color='ARI')
fig.show()