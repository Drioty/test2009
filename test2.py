a = int(input())
b = int(input())
count = 0
while (a > 0) and (b > 0):
    if a % 2 != b % 2:
        count += 1
    a = a // 2
    b = b // 2
if a > 0:
    while a > 0:
        count += 1
        a = a // 2
if b > 0:
    while b > 0:
        count += 1
        b = b // 2
print(count)