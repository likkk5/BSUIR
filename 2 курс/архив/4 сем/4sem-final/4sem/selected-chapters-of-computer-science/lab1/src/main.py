from hello import hello_world
from calculations import OPERATION, calculate
from extract_even import extract_even


def main():
    hello_world()

    try:
        result = calculate(5, 6, OPERATION.MULT)
        print('Result of mult of 5 and 6:', result)
    except ZeroDivisionError:
        print('Error: division by zero')

    list_of_numbers = [i for i in range(20)]
    filtered_list = extract_even(list_of_numbers)
    print('Result of extracting: ', filtered_list)


if __name__ == '__main__':
    main()
