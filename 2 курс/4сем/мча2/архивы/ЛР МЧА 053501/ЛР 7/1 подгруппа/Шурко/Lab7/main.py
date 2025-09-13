import functionality as func
import input


def main():
    dots = input.input_values(0, 4, 5)
    print(dots)
    func.count_k(dots)
    print(func.get_cubic_interpolation_in_point(2.0))


if __name__ == '__main__':
    main()
