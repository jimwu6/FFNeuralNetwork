import random

names = ['train1.txt', 'valid1.txt', 'test1.txt']
data0 = 'data_banknote_0.txt'
data1 = 'data_banknote_1.txt'
d = [data0, data1]

for i in range(len(d)):
    # open files
    lines = open(d[i]).readlines()
    # shuffle the lines
    random.shuffle(lines)

    # create bounds
    size = len(lines)
    a = int(size*0.6)
    b = a + int(size*0.2)

    # separate arrays
    train = lines[:a]
    valid = lines[a:b]
    test = lines[b:]

    # add to new files
    open(names[0], 'a').writelines(train)
    open(names[1], 'a').writelines(valid)
    open(names[2], 'a').writelines(test)


# shuffle train dataset
lines = open(names[0]).readlines()
random.shuffle(lines)
open(names[0], 'w').writelines(lines)


