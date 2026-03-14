def palindrome(s):
    cleaned = "".join(char.lower() for char in s if char.isalnum())
    return cleaned == cleaned[::-1]

s = input()
if palindrome(s):
    print("Palindrome")
else:
    print("Not palindrome")