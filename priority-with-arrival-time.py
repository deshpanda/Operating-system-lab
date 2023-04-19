from heapq import *
from collections import *
from tabulate import tabulate
# preemptive priority scheduling
n = int(input("No. of Tasks: "))
print("Enter arrival time,burst time and priority ")
l = []
d = defaultdict(list)
o = 0
for i in range(n):
    a, b, p = map(int, input().split())
    o = max(o, a)
    l.append([a, b])
    d[a].append([p, b, i])

buffer = []
time = 0
ans = [0]*n
for i in range(o+1):
    time += 1
    if i in d:
        for i in d[i]:
            heappush(buffer, i)
    if buffer:
        p, bst, idx = heappop(buffer)
        bst -= 1
        if bst:
            heappush(buffer, [p, bst, idx])
        else:
            ans[idx] = time

while buffer:
    time += 1
    p, bst, idx = heappop(buffer)
    bst -= 1
    if bst:
        heappush(buffer, [p, bst, idx])
    else:
        ans[idx] = time
head = ["AT", "BT", "CT", "WT", "TAT"]
ok = []
for i in range(n):
    ok.append([l[i][0], l[i][1], ans[i], ans[i] -
               l[i][0]-l[i][1], ans[i]-l[i][0]])

print(tabulate(ok, headers=head, tablefmt="grid"))

## 5
## 0 3 3
## 1 6 4
## 3 1 9
## 2 2 7
## 4 4 8
