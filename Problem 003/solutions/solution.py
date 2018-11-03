line = input()
(n, m) = line.split(' ')

n = int(n)
m = int(m)

isA, hasA = [], []

for i in range(n):
    rel = input().split(' ')
    if (rel[1] == "is-a"):
        isA.append((rel[0], rel[2]))
    elif (rel[1] == "has-a"):
        hasA.append((rel[0], rel[2]))


for i in range(m):
    que = input().split(' ')
    if (que[1] == "is-a"):
        for j in isA:
            if (rel[0], rel[2]) = isA()
    elif (que[1] == "has-a"):
        hasA.append((rel[0], rel[2]))
