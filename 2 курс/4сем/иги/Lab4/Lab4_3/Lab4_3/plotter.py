import matplotlib.pyplot as plt

def plot_functions(x_values, func_values, math_func_values, n):
    """
    Plot the series expansion and math function comparison.

    Args:
        x_values (list): List of x values for plotting.
        func_values (list): List of function values calculated using series expansion.
        math_func_values (list): List of function values calculated using math module.
        n (int): Number of terms used in the series expansion.

    Returns:
        None
    """
    plt.plot(x_values, func_values, label=f'Sum of {n} terms')
    plt.plot(x_values, math_func_values, label='Math Function')
    plt.xlabel('x')
    plt.ylabel('F(x)')
    plt.title('Comparison of Series Expansion and Math Function')
    plt.legend()
    plt.grid(True)
    plt.savefig('plot.png')
    plt.show()

# def save_plot():
#     plt.savefig('plot.png')

