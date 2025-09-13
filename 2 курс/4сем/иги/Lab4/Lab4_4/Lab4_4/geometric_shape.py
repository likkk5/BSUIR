from abc import ABC, abstractmethod

class GeometricShape(ABC):
    """Abstract class for geometric shapes."""#определение общего интерфейса дл различных реализаций
    @abstractmethod
    def area(self):
        """Abstract method to compute the area of the shape.""" #объ€вление метода без конкретной реализации
        pass

class Color:
    """Class to represent the color of a shape."""
    def __init__(self, color):
        self._color = color

    @property
    def color(self):
        """Get the current color."""
        return self._color

    @color.setter
    def color(self, new_color):
        """Set a new color."""
        self._color = new_color

