import os

for i in range(1,7):
    cmd = "./grid --debug dat%s.txt > output%s.txt" % (i,i)
    print(cmd)
    os.system(cmd)
