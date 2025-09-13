import numpy
from numpy import linalg as LA
from sympy import *

n = 5
#a = numpy.array(float) 
bB = numpy.array(1, float)
a = numpy.array ([
    [3.1300,  0.8100,  1.4700,  0.9200, -0.5300],
    [0.8100,  3.1300 , 0.8100,  1.4700,  0.9200],
    [1.4700,  0.8100,  3.1300,  0.8100,  1.7200],
    [0.9200 , 1.4700 , 0.8100,  3.1300, -0.5300],
    [-0.5300 , 0.9200,  1.7200, -0.5300, 3.1300]
    ])
lis_ed = [0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1]
for i in range(n**2-1):
    #a = numpy.append(a,lis[i])
    bB = numpy.append(bB,lis_ed[i])
    

a = a.reshape((n, n))
bB = bB.reshape((n, n))
print(a)
print(bB)

def danilevskiy_method(a, k):
    global bB
    b1 = numpy.array([1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1],float) 
    b1 = b1.reshape((n, n))
    if a[n-k][n-k-1] == 0:
        return 1
    else:
        for i in range(n):
            for j in range(n):
                if i == n-k-1:
                    if j != n-k-1:
                        b1[n-k-1][j] = round((-1)*float(a[n-k][j])/float(a[n-k][n-k-1]),4)
                    else: 
                        b1[n-k-1][n-k-1] = round(1/a[n-k][n-k-1],4)
                else:
                    if i == j:
                        b1[i][j] = 1
                    else:
                        b1[i][j] = 0

    bB = bB.dot(b1)
    c = a.dot(b1)
    b1_minus_1 = LA.inv(b1)
    d = b1_minus_1.dot(c)
    return d

print(a)
print()
b = danilevskiy_method(a,1)
print(b)
print()
c = danilevskiy_method(b,2)
print(c)
print()
d = danilevskiy_method(c,3)
print(d)
print()
e = danilevskiy_method(d,4)
print(e)
print()

print('bB', bB)

w,v = numpy.linalg.eig(a)

#x = Symbol('x')
#solution = solve(x**3+5*x**2+4.85*x-4.25, x)

#y1 = [solution[0]**2, solution[0], 1]
#y2 = [solution[1]**2, solution[1], 1]
#y3 = [solution[2]**2, solution[2], 1]

#vec1 = bB.dot(y1)
#vec2 = bB.dot(y2)
#vec3 = bB.dot(y3)

print('the vec1 is',v[0])
print('the vec2 is',v[1])
print('the vec3 is',v[2])

#print('the solution is ', solution)


#b = a.reshape((4, 4))
#print(a)


print('w is', w)
print('v is', v)
