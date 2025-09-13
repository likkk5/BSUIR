from arcsin_calculator import ArcsinSeriesCalculator
from sequence_statistics import SequenceStatistics
from plotter import plot_functions
import math

def main():
    arcsin_calculator = ArcsinSeriesCalculator()

    while True:
        x = ArcsinSeriesCalculator.validate_float_input("Enter the value of x (-1 < x < 1): ")
        if abs(x) >= 1:
            print("Error: |x| must be less than 1.")
            continue

        eps = ArcsinSeriesCalculator.validate_float_input("Enter the desired precision (eps): ")
        if eps <= 0:
            print("Error: Precision (eps) must be positive.")
            continue

        print("\nResult:")
        print("x\t F(x)\t\t n\t Math F(x)")
        print("-" * 40)
        calculated_value, terms = arcsin_calculator.calculate_arcsin_series(x, eps)
        math_value = math.asin(x)
        print(f"{x:.4f}\t {calculated_value:.6f}\t {terms}\t {math_value:.6f}")

        # Analyze sequence statistics
        sequence = [calculated_value for _ in range(terms)]
        stats = SequenceStatistics(sequence)
        print("\nSequence Statistics:")
        print("Mean:", stats.mean())
        print("Median:", stats.median())
        print("Mode:", stats.mode()) 
        print("Variance:", stats.variance())
        print("Standard Deviation:", stats.std_deviation())
        
        # Plot functions
        x_values = [i / 10 for i in range(-10, 11)]
        series_values = [arcsin_calculator.calculate_arcsin_series(x_val, eps)[0] for x_val in x_values]
        math_func_values = [math.asin(x_val) for x_val in x_values]
        plot_functions(x_values, series_values, math_func_values, terms)

        choice = input("\nDo you want to calculate again (Y/N)? ").upper()
        if choice != 'Y':
            break

if __name__ == "__main__":
    main()
