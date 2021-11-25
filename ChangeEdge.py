
F = open("EdgeSolInv.txt","r")
n = 479001600
for i in range(n):
    R = F.readline()
    x,y = R.split(":")
    if(int(x[:-1]) == 96754480):
        print(R)
        print(y)
print("finish1")

F.close()