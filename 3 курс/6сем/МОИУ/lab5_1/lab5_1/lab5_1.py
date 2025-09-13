import numpy.linalg

def nord_west_method(a, b):
    """
    Метод северо-западного угла для получения начального решения транспортной задачи.

    a: Вектор поставок.
    b: Вектор спроса.
    
    Возвращает:
    x: Начальное распределение поставок по маршрутам.
    basis_cells: Множество базисных клеток.
    """
    num_rows = len(b)  
    num_columns = len(a)  
    x = [[0] * num_rows for _ in range(num_columns)] 
    row, col = 0, 0
    basis_cells = []  

    # Заполнение матрицы x методом северо-западного угла
    while True:
        basis_cells.append((row, col))  # Добавляем текущую базисную клетку
        max_supply = min(a[row], b[col])  # Минимум из оставшихся поставок и спроса
        a[row] -= max_supply  # Уменьшаем количество поставок
        b[col] -= max_supply  
        x[row][col] = max_supply

        # Если дошли до конца, завершаем
        if row == num_columns - 1 and col == num_rows - 1:
            break
        if a[row] == 0 and row != len(a) - 1:
            row += 1  # Переходим к следующей строке, если поставка закончилась
        elif b[col] == 0 and col != len(b) - 1:
            col += 1  # Переходим к следующему столбцу, если спрос завершен

    return x, basis_cells

def get_potentials(c, basis_cells):
    """
    Рассчитывает потенциалы u и v для каждой клетки.

    c: Матрица затрат.
    basis_cells: Множество базисных клеток.
    
    Возвращает:
    u: Потенциалы для строк.
    v: Потенциалы для столбцов.
    """
    num_rows = len(c)
    num_columns = len(c[0])
    augmented_matrix = [[0] * (num_columns + num_rows) for _ in range(num_columns + num_rows)]  # Матрица для решения системы
    right_hand_side = [0] * (num_columns + num_rows)  # Вектор правых частей

    augmented_matrix[-1][0] = 1  # Дополнительное уравнение для у
    right_hand_side[-1] = 0

    # Заполняем систему уравнений для потенциалов
    for idx, (row, col) in enumerate(basis_cells):
        augmented_matrix[idx][row] = augmented_matrix[idx][num_rows + col] = 1
        right_hand_side[idx] = c[row][col]

    # Решаем систему
    potentials = numpy.linalg.solve(augmented_matrix, right_hand_side)
    return potentials[:num_rows], potentials[num_rows:]

def rebuild_basis_cells(num_rows, num_columns, basis_cells):
    """
    Разбивает множество базисных клеток на горизонтальные и вертикальные группы.

    Возвращает:
    horizontal_groups: Список для строк.
    vertical_groups: Список для столбцов.
    """
    horizontal_groups, vertical_groups = [[] for _ in range(num_rows)], [[] for _ in range(num_columns)]

    for row, col in basis_cells:
        horizontal_groups[row].append(col)
        vertical_groups[col].append(row)
    return horizontal_groups, vertical_groups

def get_basis_matrix(num_rows, num_columns, basis_cells):
    """
    Строит матрицу, отображающую базисные клетки.

    Возвращает:
    basis_matrix: Матрица, где 1 — это базисная клетка, 0 — не базисная.
    """
    basis_matrix = [[0] * num_columns for _ in range(num_rows)]

    for row, col in basis_cells:
        basis_matrix[row][col] = 1

    return basis_matrix

def index_generator(num_rows, num_columns):
    """
    Генератор для обхода всех клеток матрицы.

    Возвращает:
    row_index, col_index: Индексы клеток.
    """
    for row_index in range(num_rows):
        for col_index in range(num_columns):
            yield row_index, col_index

def transport_task_solver(a, b, c):
    """
    Решает транспортную задачу методом потенциалов.

    a: Вектор поставок.
    b: Вектор спроса.
    c: Матрица затрат.
    """
    num_rows = len(a)
    num_columns = len(b)

    # Балансировка поставок и спроса
    difference = sum(a) - sum(b)
    if difference != 0:
        if difference > 0:
            b.append(difference)
            num_columns += 1
            for row in c:
                row.append(0)
        elif difference < 0:
            a.append(-difference)
            num_rows += 1
            c.append([0] * num_columns)

    # Получаем начальное решение методом северо-западного угла
    x, basis_cells = nord_west_method(a, b)

    while True:
        u, v = get_potentials(c, basis_cells)  # Вычисляем потенциалы
        basis_matrix = get_basis_matrix(num_rows, num_columns, basis_cells)  # Строим матрицу базисных клеток

        # Поиск кандидата для улучшения плана
        for row_index, col_index in index_generator(num_rows, num_columns):
            if basis_matrix[row_index][col_index] == 0 and u[row_index] + v[col_index] > c[row_index][col_index]:
                basis_matrix[row_index][col_index] = 1
                basis_cells.append((row_index, col_index))
                break
        else:
            # Если улучшений нет, выводим итоговый план
            print("\nИтоговый оптимальный план: ")
            for i in range(num_rows):
                for j in range(num_columns):
                    print(x[i][j], end='\t')
                print()
            return

        horizontal_groups, vertical_groups = rebuild_basis_cells(num_rows, num_columns, basis_cells)  # Обновляем горизонтальные и вертикальные группы

        # Строим цикл перераспределения
        loop = []
        loop.append((row_index, col_index))
        deleted = True
        while deleted:
            deleted = False
            for row_index, row in enumerate(horizontal_groups):
                if len(row) < 2:
                    for col_index in row:
                        vertical_groups[col_index].remove(row_index)
                        deleted = True
                    row.clear()
            for col_index, column in enumerate(vertical_groups):
                if len(column) < 2:
                    for row_index in column:
                        horizontal_groups[row_index].remove(col_index)
                        deleted = True
                    column.clear()

        up = True
        row_index, col_index = loop[0]
        # Перераспределение по циклу
        while True:
            if up:
                up = False
                row_index = vertical_groups[col_index][1] if vertical_groups[col_index][0] == row_index else vertical_groups[col_index][0]
            else:
                up = True
                col_index = horizontal_groups[row_index][1] if horizontal_groups[row_index][0] == col_index else horizontal_groups[row_index][0]
            if row_index == loop[0][0] and col_index == loop[0][1]:
                break
            else:
                loop.append((row_index, col_index))

        # Вычисляем параметр θ — минимальное значение в цикле
        min_value_in_cycle = min(x[loop[i][0]][loop[i][1]] for i in range(1, len(loop), 2))
        sign_factor = 1
        # Корректируем значения в цикле
        for row_index, col_index in loop:
            x[row_index][col_index] += sign_factor * min_value_in_cycle
            if x[row_index][col_index] == 0 and len(basis_cells) > num_columns + num_rows - 1 and sign_factor == -1:
                basis_cells.remove((row_index, col_index))
            sign_factor = -1 if sign_factor == 1 else 1

def main():
    a = [100, 300, 300]  
    b = [300, 200, 200]  
    c = [[8, 4, 1],      
         [8, 4, 3],
         [9, 7, 5]]
    
    # Вывод входных данных
    print("Входные данные для транспортной задачи:")
    print("Вектор поставок (a):", a)
    print("Вектор спроса (b):", b)
    print("Матрица затрат (c):")
    for row in c:
        print(row)
    
    print("\nРешение транспортной задачи методом потенциалов")
    transport_task_solver(a, b, c)

if __name__ == "__main__":
    main()
