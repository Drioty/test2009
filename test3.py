n = int(input())
i = 2
print(n, '= ', end='')
while (i <= n):
    while (n % i == 0):
        if n // i == 1:
            print(i)
        else:
            print(i, '* ', end='')
        n = n // i
    i += 1
