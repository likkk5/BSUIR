from shapes import IsoscelesTriangle
from input_validation import validate_input, validate_color
import matplotlib.pyplot as plt
import numpy as np

def get_user_input(prompt):
    """Prompt the user for input."""
    return input(prompt)

def plot_triangle(triangle):
    """Plot the triangle."""
    plt.figure()
    plt.plot([0, triangle.base, triangle.base / 2, 0], [0, 0, triangle.height, 0], color=triangle.color.color)
    plt.fill([0, triangle.base, triangle.base / 2, 0], [0, 0, triangle.height, 0], color=triangle.color.color, alpha=0.5)
    plt.text(triangle.base / 2, triangle.height / 2, triangle.label, horizontalalignment='center', verticalalignment='center')
    
    # Первая точка (0, 0) - начальная точка треугольника, левый нижний угол.
    # Вторая точка (triangle.base, 0) - конец основания треугольника, правый нижний угол.
    # Третья точка (triangle.base / 2, triangle.height) - верхний угол треугольника, находится на высоте triangle.height от основания и находится посередине между началом и концом основания.
    
    plt.xlabel('Base')
    plt.ylabel('Height')
    plt.title('Isosceles Triangle')
    plt.grid(True)
    plt.savefig('plot.png')
    plt.show()

def main():
 while True:  
    # Input values from user
    base = None
    while base is None:
        base = validate_input(get_user_input("Enter the base of the triangle: "))
    
    height = None
    while height is None:
        height = validate_input(get_user_input("Enter the height of the triangle: "))

    color = None
    while color is None:
        color = validate_color(get_user_input("Enter the color of the triangle: "))  
        
    label = get_user_input("Enter the label for the triangle: ")

    # Create triangle object
    triangle = IsoscelesTriangle(base, height, color, label)

    # Display triangle information
    print(triangle)
    print("Area:", triangle.area())

    # Plot the triangle
    plot_triangle(triangle)

    # Output to file
    file_name = "triangle.txt"
    with open(file_name, "w") as file:
        file.write(str(triangle))

    print(f"Triangle details saved to {file_name}.")
    
    repeat = input("Do you want to run the program again? (y/n): ")
    if repeat.lower() != 'y':
      break
if __name__ == "__main__":
    main()
