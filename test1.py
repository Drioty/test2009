a = int(input())
b = int(input())
c = int(input())
if (a >= b) and (a >= c):
    (a, c) = (c, a)
elif (b >= c) and (b >= a):
    (b, c) = (c, b)
if (a >= b):
    (a, b) = (b, a)
print(a, b, c)
