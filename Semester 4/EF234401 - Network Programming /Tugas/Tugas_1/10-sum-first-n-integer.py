n = int(input())

if n > 0:
    sumOfn = n * (n + 1) // 2
    print(int(sumOfn))
elif n < 0:
    absolute_n = abs(n)
    sumOfn = -(absolute_n * (absolute_n + 1) // 2)
    print(int(sumOfn))
else:
    print(0)
