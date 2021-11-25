F = open("SolInv_18.txt",'r')
R = open("SolInv_18_2.txt",'w')
count = 0
for line in F.readlines():
    R.write(line[4:])
    count += 1
F.close()
R.close()