import csv

folder = './main_data/'
names = ['train.txt', 'valid.txt', 'test.txt']
newnames = ['train.dat', 'valid.dat', 'test.dat']

for i in range(len(names)):
    lines = open(folder+names[i]).readlines()
    for j in range(len(lines)):
        lines[j] = lines[j].replace(',', '\t')
    open(folder+newnames[i], 'w').writelines(lines)
