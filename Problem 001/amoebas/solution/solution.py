
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


sec = []
for i in range(int(arrDim[1])):
    sec.append(isInLoop(getPoint(i, arrData[1])))


print(arrData, arrDim)

print(sec)