a = int(input('Enter a: '))
b = int(input('Enter b: '))
c = int(input('Enter c: '))

if a == 0:
    print('Not a quadratic equations')
    exit(0)

sqrtD = (b * b - 4 * a * c) ** 0.5
x1 = (- b - sqrtD) / (2 * a)
x2 = (- b + sqrtD) / (2 * a)

print(f'{x1=} {x2=}')



