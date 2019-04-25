# -*- coding: utf-8 -*-

import pandas as pd
import matplotlib.pyplot as plt

def init_df(file_in):
    df = pd.read_csv(file_in)
    df = df.rename(index = lambda x : x * 2)
    return df

def end_df(file_out):
    df.plot.line(figsize = (100,100), grid = True)
    plt.savefig(file_out, bbox_inches='tight')


df = init_df("results/scores.csv")
df.drop(df.columns[[3,7,11,15,16,17,18,19,23,27,31,35,36,37,38,39,46,47]], axis = 1, inplace = True)
end_df("results/scores_raw.png")
for lines in range (2,25):
    df.iloc[[lines]] /= df.iat[lines, 21]
end_df("results/scores_vssake.png")

df = init_df("results/scores.csv")
df.drop(df.columns[[2,3,6,7,10,11,14,15,16,17,18,19,22,23,26,27,30,31,34,35,36,37,38,39,43,45,46,47]], axis = 1, inplace = True)
for lines in range (2,25):
    df.iloc[[lines]] /= df.iat[lines, 14]
end_df("results/scores_nokasu_vssake.png")

df = init_df("results/scores.csv")
df.drop(df.columns[[0,1,3,4,5,7,8,9,11,12,13,15,16,17,18,19,20,21,23,24,25,27,28,29,31,33,35,36,37,38,39,40,41,42,44,46,47]], axis = 1, inplace = True)
for lines in range (2,25):
    df.iloc[[lines]] /= df.iat[lines, 7]
end_df("results/scores_onlykasu_vssake.png")


df = init_df("results/scoresno.csv")
df.drop(df.columns[[3,7,8,9,10,11,15,16,17,18,19,23,27,31,35,36,37,38,39,46,47]], axis = 1, inplace = True)
end_df("results/scoresno_raw.png")

df = init_df("results/scoresno.csv")
df.drop(df.columns[[2,3,6,7,8,9,10,11,14,15,16,17,18,19,22,23,26,27,30,31,34,35,36,37,38,39,43,45,46,47]], axis = 1, inplace = True)
end_df("results/scoresno_nokasu_raw.png")

df = init_df("results/scoresno.csv")
df.drop(df.columns[[0,1,3,4,5,7,8,9,10,11,12,13,15,16,17,18,19,20,21,23,24,25,27,28,29,31,33,35,36,37,38,39,40,41,42,44,46,47]], axis = 1, inplace = True)
end_df("results/scoresno_onlykasu_raw.png")


df = init_df("results/yakus.csv")
end_df("results/yakus_raw.png")
df['Sankou'] += df['Shikou'] + df['Ame-shikou'] + df['Gokou']
df = df.rename(columns = {'Sankou': 'Kouyaku'}, inplace = True)
df.drop(df.columns[[4,5,6]], axis = 1, inplace = True)
end_df("results/yakus_kouyaku_raw.png")


df = init_df("results/yakusno.csv")
end_df("results/yakusno_raw.png")
df['Sankou'] += df['Shikou'] + df['Ame-shikou'] + df['Gokou']
df = df.rename(columns = {'Sankou': 'Kouyaku'})
df.drop(df.columns[[4,5,6]], axis = 1, inplace = True)
end_df("results/yakusno_kouyaku_raw.png")