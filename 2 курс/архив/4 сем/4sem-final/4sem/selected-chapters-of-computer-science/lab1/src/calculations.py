from enum import Enum


class OPERATION(Enum):
    ADD = 'add'
    SUB = 'sub'
    DIV = 'div'
    MULT = 'mult'


def calculate(a: int | float, b: int | float, operation: OPERATION) -> int | float:
    match operation:
        case OPERATION.DIV:
            return a / b
        case OPERATION.ADD:
            return a + b
        case OPERATION.MULT:
            return a * b
        case OPERATION.SUB:
            return a - b
