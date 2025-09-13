import functionality
import examples


if __name__ == '__main__':
    matrix_a = examples.input_values()
    functionality.main(matrix_a, examples.input_values, 4)
    matrix_b = examples.input_values1()
    functionality.main(matrix_b, examples.input_values1, 10)
    matrix_с = examples.input_values2()
    functionality.main(matrix_с, examples.input_values2, 3)
