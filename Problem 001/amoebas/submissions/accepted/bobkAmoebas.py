#!/usr/bin/python2

def removeBorder(i,j):
    if i >= 0 and i < m and j >= 0 and j < n and pic[i][j] == '#':
        pic[i][j] = '.'
        removeBorder(i,j+1)
        removeBorder(i,j-1)
        removeBorder(i-1,j+1)
        removeBorder(i-1,j-1)
        removeBorder(i+1,j+1)
        removeBorder(i+1,j-1)
        removeBorder(i-1,j)
        removeBorder(i+1,j)

line = raw_input()
(m,n) = line.split(' ')
m = int(m)
n = int(n)

pic = []
for i in range(m):
    line = raw_input()
    pic.append(list(line))

nAmoebas = 0

for i in range(m):
    for j in range(n):
        if pic[i][j] == '#':
            nAmoebas += 1
            removeBorder(i,j)

print(nAmoebas)
