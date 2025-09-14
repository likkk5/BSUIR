from typing import List

MAXN = 16


class BinNumber:
    def __init__(self, x, size):
        if isinstance(x, list):
            if len(x) != size:
                raise ValueError
            self.data = x
        elif isinstance(x, int):
            sgn = (x >> (size - 1)) & 1
            if (sgn == 0 and x < 0) or (sgn == 1 and x >= 0):
                raise OverflowError
            self.data = [(x >> i) & 1 for i in reversed(range(size))]
        else:
            raise TypeError
        self.size = size

    def __sub__(self, other):
        return self + self.neg(other)

    def __add__(self, other):
        res = BinNumber(0, self.size)
        for i in reversed(range(self.size)):
            res.data[i] += self.data[i] + other.data[i]
            if i - 1 >= 0:
                res.data[i - 1] += res.data[i] // 2
            res.data[i] %= 2

        if self.data[0] == other.data[0] and self.data[0] != res.data[0]:
            raise OverflowError

        return res

    def __rshift__(self, n):
        res = [0 for _ in range(n)]
        for i in range(len(self.data)):
            if i + n < len(self.data):
                res.append(self.data[i])
        return BinNumber(res, self.size)

    def __lshift__(self, n):
        res = [0 for _ in range(n)]
        for i in reversed(range(len(self.data))):
            if i - n >= 0:
                res.append(self.data[i])
        res.reverse()
        return BinNumber(res, self.size)

    def __mul__(self, other):
        addit = BinNumber(0, self.size)
        small = 0
        for _ in range(self.size):
            if other.data[-1] == 1 and small == 0:
                addit -= self
            elif other.data[-1] == 0 and small == 1:
                addit += self

            small = other.data[-1]
            other >>= 1
            other.data[0] = addit.data[-1]
            addit >>= 1
            addit.data[0] = addit.data[1]

        return BinNumber(addit.data + other.data, self.size * 2)

    def __divmod__(self, other):
        if other.data == [0] * other.size:
            raise ZeroDivisionError
        addit = BinNumber(self.data[:self.size // 2], self.size // 2)
        quotient = BinNumber(self.data[self.size // 2:], self.size // 2)
        for _step in range(quotient.size):
            addit <<= 1
            addit.data[-1] = quotient.data[0]
            quotient <<= 1
            prev = addit
            if other.data[0] == addit.data[0]:
                addit -= other
            else:
                addit += other
            if addit.data[0] != prev.data[0]:
                quotient.data[-1] = 0
                addit = prev
            else:
                quotient.data[-1] = 1
        if self.data[0] != other.data[0]:
            quotient = self.neg(quotient)
        return quotient, addit

    def __floordiv__(self, other):
        return self.__divmod__(other)[0]

    def __mod__(self, other):
        return self.__divmod__(other)[1]

    def __repr__(self):
        if self.data[0] == 1:
            return f'BinNumber({-int("".join(map(str, self.neg(self).data)), 2)})'
        else:
            return f'BinNumber({(int("".join(map(str, self.data)), 2))})'

    def __str__(self):
        return "".join(map(str, self.data))

    @staticmethod
    def neg(x):
        return BinNumber([1 - e for e in x.data], x.size) + BinNumber(1, x.size)


n = int(input('Please enter first number: '))
m = int(input('Please enter second number: '))

while True:
    op = input('Please choose the operation (+,-,*,/,%): ')
    if op not in ('+', '-', '*', '/', '%'):
        print('Wrong operation, try again')
    else:
        break

if op == '/' or op == '%':
    sn = BinNumber(n, MAXN * 2)
else:
    sn = BinNumber(n, MAXN)

sm = BinNumber(m, MAXN)

print(f' {sn} == {sn.__repr__()}')
print(op)
print(f' {sm} == {sm.__repr__()}')

if op == '+':
    res = sn + sm
elif op == '-':
    res = sn - sm
elif op == '*':
    res = sn * sm
elif op == '/':
    res = sn // sm
elif op == '%':
    res = sn % sm
else:
    raise ArithmeticError

print(' -------------------')
print(f' {res} == {res.__repr__()}')
