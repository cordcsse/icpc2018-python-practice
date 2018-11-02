
f = open("..\\data\\sample\\1.in")
arrDim = f.readline().strip().split(sep=" ")
arrData = f.read().splitlines()
f.close()


def getSegment(index, data):
    return(data[index])

def getPoint(index, segment):
    return(segment[index])

def isInLoop(point):
    if point == ".":
        return False
    elif point == "#":
        return True

def isAttached(p, q):
    if (p[0] == q[0] or p[0]+1 == q[0] or p[0]-1 == q[0]) and (p[1] == q[1] or p[1]+1 == q[1] or p[1]-1 == q[1]):
        return True

def formSegment(p, q):
    if type(p) == type([]):
        for i in p:
            return True

def findLoops(dim, data):
    dim[0], dim[1] = int(dim[0]), int(dim[1])

    loopSeg = []

    for i in range(dim[0]):
        for j in range(dim[1]):
            if isInLoop(data[i][j]):
               loopSeg.append((j,i))
    return(loopSeg)


findLoops(arrDim, arrData)

sec = []
for i in range(int(arrDim[1])):
    sec.append(isInLoop(getPoint(i, arrData[1])))


print(arrData, arrDim)

print(sec)

print("\n", findLoops(arrDim, arrData))

print(isAttached((1,1), (3,1)))