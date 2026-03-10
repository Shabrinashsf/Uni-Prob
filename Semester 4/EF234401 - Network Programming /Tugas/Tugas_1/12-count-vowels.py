vowelsLower = ['a', 'e', 'i', 'o', 'u']
vowelsUpper = ['A', 'E', 'I', 'O', 'U']

s = input()
while s != 'END':
    count = 0
    for i in s:
        if i in vowelsLower or i in vowelsUpper:
            count += 1
    print(count)
    break