s = input()

if s.startswith('-'):
    s = s[1:]

sumOfDigits = 0
for digit in s:
    sumOfDigits += int(digit)

print(sumOfDigits)
