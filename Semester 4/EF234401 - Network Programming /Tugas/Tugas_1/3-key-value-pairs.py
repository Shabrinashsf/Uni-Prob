n = int(input())
pairs = {}

for _ in range(n):
    line = input().split()
    key = line[0]
    value = int(line[1])
    pairs[key] = value

k = input()
print(pairs[k])