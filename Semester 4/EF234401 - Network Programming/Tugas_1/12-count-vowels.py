vowels = "aeiouAEIOU"

s = input()

count = 0
for char in s:
    if char in vowels:
        count += 1

print(count)