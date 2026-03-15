n = int(input())
sum = 0
for i in range (n, 0, -1):
    p = int(input())
    if p % 2 == 0:
        sum += p
print(sum)
    