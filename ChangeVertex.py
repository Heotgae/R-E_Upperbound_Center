F = open("VertexSolInv.txt",'r')
for i in range(11520):
    s = F.readline()
    x,y = s.split(":")
    if(int(x[:-1]) == 2496171):
        print(y)