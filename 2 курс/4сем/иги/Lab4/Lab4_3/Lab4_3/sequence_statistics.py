import math
from validate_float_input import InputValidator

class SequenceStatistics(InputValidator):
    """
    A class to perform statistical analysis on a sequence of data.

    Attributes:
        data (list): The sequence of data for which statistics are calculated.

    Methods:
        mean(): Calculate the mean (average) of the data.
        median(): Calculate the median (middle value) of the data.
        mode(): Calculate the mode (most common value) of the data.
        variance(): Calculate the variance of the data.
        std_deviation(): Calculate the standard deviation of the data.
    """

    def __init__(self, data):
        """
        Initialize the SequenceStatistics object with the provided data.

        Args:
            data (list): The sequence of data for which statistics will be calculated.
        """
        self.data = data

    def mean(self):
        """
        Calculate the mean (average) of the data.

        Returns:
            float: The mean value of the data.
        """
        return sum(self.data) / len(self.data)

    def median(self):
        """
        Calculate the median (middle value) of the data.

        Returns:
            float: The median value of the data.
        """
        sorted_data = sorted(self.data)
        n = len(sorted_data)
        if n % 2 == 0:
            return (sorted_data[n // 2 - 1] + sorted_data[n // 2]) / 2
        else:
            return sorted_data[n // 2]

    def mode(self):
        """
        Calculate the mode (most common value) of the data.

        Returns:
            list: A list of mode values of the data.
        """
        counts = {x: self.data.count(x) for x in self.data}
        max_count = max(counts.values())
        modes = [x for x, count in counts.items() if count == max_count]
        return modes

    def variance(self):
        """
        Calculate the variance of the data.

        Returns:
            float: The variance of the data.
        """
        mean = self.mean()
        return sum((x - mean) ** 2 for x in self.data) / len(self.data)

    def std_deviation(self):
        """
        Calculate the standard deviation of the data.

        Returns:
            float: The standard deviation of the data.
        """
        return math.sqrt(self.variance())


