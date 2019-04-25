# -*- coding: utf-8 -*-

cards = ["Crane", "Aka1", "Kasu11", "Kasu12",
					"Nightingale", "Aka2", "Kasu21", "Kasu22",
					"Curtain", "Aka3", "Kasu31", "Kasu32",
					"Cuckoo", "Tan4", "Kasu41", "Kasu42",
					"Bridge", "Tan5", "Kasu51", "Kasu52",
					"Butterflies", "Ao6", "Kasu61", "Kasu62",
					"Boar", "Tan7", "Kasu71", "Kasu72",
					"Moon", "Geese", "Kasu81", "Kasu82",
					"Sake", "Ao9", "Kasu91", "Kasu92",
					"Deer", "AoA", "KasuA1", "KasuA2",
					"Rain", "Swallow", "TanB", "Lightning",
					"Phoenix", "KasuC1", "KasuC2", "KasuC3"]

yakus = ["Kasu", "Tane", "Tan", "Sankou", "Ame-shikou",
"Shikou", "Gokou", "Ino-shika-chou", "Akatan", "Aotan",
"Hanami-zake", "Tsukimi-zake"]

files = [("scores", cards), ("scoresno", cards),
         ("yakus", yakus), ("yakusno", yakus[:-2])]

for file_n_header in files:
    file = file_n_header[0]
    header = file_n_header[1]
    with open("results/" + file + ".csv", "w") as score:
        line = ""
        for i in range (len(header)):
            line += header[i] + ","
        score.write(line[:-1] + "\n")
        for i in range (0, 50, 2):
            cpt = 0
            with open("results/" + file + str(i) + ".txt") as myfile:
                line = ""
                for lines in myfile.readlines():
                    cpt += 1
                    if cpt % 3 == 2:
                        line += lines.strip() + ","
                score.write(line[:-1] + "\n")