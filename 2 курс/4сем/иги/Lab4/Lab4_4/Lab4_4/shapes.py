from geometric_shape import GeometricShape, Color

class IsoscelesTriangle(GeometricShape):
    """Class representing an isosceles triangle."""
    def __init__(self, base, height, color, label):
        """Initialize the triangle with specified parameters."""
        self.base = base
        self.height = height
        self.color = Color(color)
        self.label = label

    def area(self):
        """Compute the area of the triangle."""
        return 0.5 * self.base * self.height

    def __str__(self):
        """Return a string representation of the triangle."""
        return f"Isosceles triangle with base {self.base}, height {self.height}, color {self.color.color}, label {self.label}, area {self.area()}"

