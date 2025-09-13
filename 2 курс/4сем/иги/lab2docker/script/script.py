import math
def circle_area(r):
    return math.pi * r * r


def circle_perimeter(r):
    return 2 * math.pi * r

def square_area(a):
    return a * a


def square_perimeter(a):
    return 4 * a

r = int(input("Input the radius of circle:"))
print("The area of this circle:", circle_area(r), '\n')
print ("The perimeter of this circle:", circle_perimeter(r), '\n')

a = int(input("Input the side of square:"))
print("The area of this square:", square_area(a), '\n')
print ("The perimeter:", square_perimeter(a), '\n') 
