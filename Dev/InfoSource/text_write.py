import pandas as pd
for val in range(20):
    dfs = pd.read_csv('std_7.csv')
    dfs = dfs.sample(frac = 1)
    with open(f"./std_7/std_{val}.txt", 'w') as f:
        i = 0
        for index, row in dfs.iterrows():
            f.write(
                f'INSERT INTO chameleon_ds4_clean VALUES({i}, {row["x"]}, {row["y"]}, {i}); \n')
            i = i + 1
    with open(f"./std_7/std_{val}.csv", 'w') as f:
        i = 0
        for index, row in dfs.iterrows():
            f.write(
                f'{row["x"]}, {row["y"]}, {row["class"]}\n')
            i = i + 1