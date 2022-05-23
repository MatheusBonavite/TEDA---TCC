import pandas as pd
dfs = pd.read_csv('chameleon-ds4-clean.csv')
with open('readme.txt', 'w') as f:
    for index, row in dfs.iterrows():
        f.write(
            f'INSERT INTO chameleon_ds4_clean VALUES({index+1}, {row["x"]}, {row["y"]}, {index+1}); \n')
