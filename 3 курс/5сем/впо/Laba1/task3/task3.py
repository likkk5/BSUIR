# -*- coding: windows-1251 -*-
def calculate_area(length, width):
    # Проверка, что входные данные — это числа
    if not isinstance(length, (int, float)) or not isinstance(width, (int, float)):
        raise ValueError("Длина и ширина должны быть числами.")
    if length <= 0 or width <= 0:
        raise ValueError("Длина и ширина должны быть положительными числами.")
    
    return length * width

def main():
    while True:
        try:

            # Ввод длины и ширины 
            length_input = input("Введите длину прямоугольника: ").strip()
            if not length_input:
                raise ValueError("Длина не может быть пустой строкой.")
            length = float(length_input)
            
            width_input = input("Введите ширину прямоугольника: ").strip()
            if not width_input:
                raise ValueError("Ширина не может быть пустой строкой.")
            width = float(width_input)
            
            # Вычисление площади
            area = calculate_area(length, width)
            print(f"Площадь прямоугольника: {area}")
            break 
        
        except ValueError as e:
            print(f"Ошибка: {e}. Пожалуйста, введите корректные числовые значения.")

if __name__ == "__main__":
    main()

