def fib(n):
    if n <= 0: return 0
    
    a, b = 0, 1
    for _ in range(n):
        a, b = b, a + b
    
    return a

n = int(input())
print(fib(n))