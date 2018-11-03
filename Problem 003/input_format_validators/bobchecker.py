# checks for n,m values, loops in "is-a" relations, duplicate relations,
# number of names

import sys

line = raw_input().split()
n = int(line[0])
m = int(line[1])
if n < 1 or n > 10000:
  print "bad n value:",n
if m < 1 or m > 10000:
  print "bad m value:",m

names = []
rels = []

for i in range(n):
  line = raw_input().split()
  if len(line) != 3:
    print "line",(i+1),"wrong number of inputs"

  left = line[0]
  if not left.isalpha():
    print "line",(i+2),": non-alpha string",left
  rel = line[1]
  right = line[2]
  if not right.isalpha():
    print "line",(i+2),": non-alpha string",right
  if left not in names:
    names.append(left)
  if right not in names:
    names.append(right)
  if rel not in ['is-a','has-a']:
    print "line",(i+2),"invalid relation:",rel
  if (left,rel,right) in rels:
    print "line",(i+2),": duplicate relation",(left,rel,right)
  elif left==right and rel=="is-a":
    print "line",(i+2),": identity relation",left,"is-a",right
  else:
    rels.append((left,rel,right))

if len(names) > 500:
  print "Too many distinct names:",len(names)

#print "A total of",len(names),"distinct names were used"
#print rels

# check for cycles in is-a:
#nodes = [[] for i in range(len(names))]
#for rel in rels:
#  l,x,r = rel
#  if x=="has-a":
#    continue
#  indl = names.index(l)
#  nodes[indl].append(r)
#
#def dfs(nm,j):
#  nm2 = names[j]
#  if nm2 in nm:
#    print "Cyclic is-a for",nm2
#    return
#  for k in nodes[j]:
#    ind = names.index(k)
#    dfs(nm+[names[j]],ind)
#
#for i in range(len(nodes)):
#  print i,names[i]
#  # dfs from node i:
#  nm = names[i]
#  for j in nodes[i]:
#    ind = names.index(j)
#    dfs([nm],ind)


for i in range(m):
  line = raw_input().split()
  if len(line) != 3:
    print "line",(i+1),"wrong number of inputs"
  left = line[0]
  if not left.isalpha():
    print "line",(i+2+n),": non-alpha string",left
  rel = line[1]
  right = line[2]
  if not right.isalpha():
    print "line",(i+2+n),": non-alpha string",right
  if left not in names:
    print "line",(i+2+n),": query uses non-existent name",left
  if right not in names:
    print "line",(i+2+n),": query uses non-existent name",right
  if rel not in ['is-a','has-a']:
    print "line",(i+2+n),"invalid query:",rel

  sys.exit(42)
