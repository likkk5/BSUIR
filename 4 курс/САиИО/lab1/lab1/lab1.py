# coding: utf-8
"""
Реализация метода отсекающих ограничений Гомори с двухфазным симплексом.
"""

import numpy as np

EPS = 1e-9

def _is_integer_vector(x, tol=1e-9):
    return np.all(np.abs(x - np.round(x)) < tol)

def fractional_part(x):
    """Возвращает дробную часть числа/вектора в [0,1)."""
    return np.mod(x, 1.0)

def print_vector(name, v):
    print(f"{name} = {np.array2string(v, formatter={'float_kind':lambda x: f'{x:.6g}'})}")

#
# ------------- Симплекс: двухфазный метод -------------
#
# Мы работаем со стандартной формой: Ax = b, x >= 0, max c^T x
# Реализуем двухфазный метод: Phase I для поиска допустимого базиса,
# затем Phase II для максимизации исходной функции.
#

def _prepare_two_phase(A, b):
    """Подготовка данных: если b_i < 0 — умножаем строку на -1."""
    A = A.copy().astype(float)
    b = b.copy().astype(float)
    m, n = A.shape
    for i in range(m):
        if b[i] < -EPS:
            A[i, :] *= -1
            b[i] *= -1
    return A, b

def _simplex_tableau_from_phaseI(A, b, c):
    """
    Строит начальную таблицу для двухфазного симплекс-решения.
    Возвращает tableau и списки индексов базиса B и небазиса N.
    Tableau форматируем как стандартную расширенную таблицу:
    [A | b]
    И отдельно вектор целевой функции.
    """
    m, n = A.shape
    # для Phase I будем добавлять искусственные переменные ai для каждой строки
    # Phase I objective: minimize sum(ai)  -> для симплекс-реализации переведём в максимизацию минимизируя -sum(ai)
    # Но удобнее прямо сформировать базис из искусственных переменных
    # Базисные индексы - последние m переменных (искусственные)
    A_phase = np.hstack((A, np.eye(m)))
    c_phase = np.hstack((c, np.zeros(m)))  # c для Phase II вставим позже; для Phase I мы сформируем отдельный вектор
    return A_phase, b, c_phase, list(range(n, n+m))  # B = искусственные

def _compute_basic_solution(A, b, B):
    """Вычислить базисное решение x: x_B = A_B^{-1} b (другие нули)."""
    m, n = A.shape
    B = list(B)
    A_B = A[:, B]
    try:
        invA_B = np.linalg.inv(A_B)
    except np.linalg.LinAlgError:
        raise RuntimeError("Базисная матрица сингулярна")
    x_B = invA_B @ b
    x = np.zeros(n)
    for i, idx in enumerate(B):
        x[idx] = x_B[i]
    return x, invA_B

def _select_entering_variable(c, A, invA_B, B, N):
    """
    Для максимизации:
    reduced costs: r_j = c_j - c_B^T * invA_B * A[:, j]
    Выбираем j с r_j > EPS (улучшающий) — используем правило Блана/макс r_j.
    """
    c = np.asarray(c)
    B = list(B)
    N = list(N)
    c_B = c[B]
    # compute y = c_B^T * invA_B
    y = c_B @ invA_B
    best_j = None
    best_r = 0.0
    for j in N:
        a_j = A[:, j]
        r_j = c[j] - y @ a_j
        if r_j > best_r + EPS:
            best_r = r_j
            best_j = j
    return best_j, best_r

def _select_leaving_variable(invA_B, A, b, entering_index, B):
    """
    Theta rule: x_B = invA_B * b. Direction d_B = invA_B * a_j.
    choose i with d_i > EPS minimizing x_B[i] / d_i
    Return (position_in_B, idx_of_leaving) or (None, None) if unbounded.
    """
    a_j = A[:, entering_index]
    d = invA_B @ a_j
    x_B = invA_B @ b
    min_ratio = None
    leave_pos = None
    for i, di in enumerate(d):
        if di > EPS:
            ratio = x_B[i] / di
            if (min_ratio is None) or (ratio < min_ratio - EPS) or (abs(ratio - min_ratio) < EPS and B[i] > B[leave_pos]):
                min_ratio = ratio
                leave_pos = i
    if leave_pos is None:
        return None, None  # unbounded
    return leave_pos, B[leave_pos], min_ratio

def _pivot(B, N, enter, leave_pos):
    """Обновляет пары B и N: на месте leave_pos из B ставим enter; N обновляется."""
    leave = B[leave_pos]
    B = list(B)
    N = list(N)
    # replace in B
    B[leave_pos] = enter
    # replace in N
    N.remove(enter)
    N.append(leave)
    N.sort()
    return B, N

def simplex_max(A, b, c, B_init=None, max_iters=1000, verbose=False):
    """
    Простейший симплекс (Phase II) при заданном начальном базисе B_init.
    Возвращает (status, x, B) где status: 'optimal', 'unbounded', 'infeasible'(не применяется здесь)
    """
    m, n = A.shape
    if B_init is None:
        raise ValueError("Simplex: требуется начальный базис B_init")
    B = list(B_init)
    N = [j for j in range(n) if j not in B]
    for it in range(max_iters):
        x, invA_B = _compute_basic_solution(A, b, B)
        # check feasibility of x_B
        if np.any(x[B] < -EPS):
            return 'infeasible', None, None
        # choose entering var
        enter, best_r = _select_entering_variable(c, A, invA_B, B, N)
        if enter is None:
            if verbose:
                print(f"Simplex: optimal found at iteration {it}")
            return 'optimal', x, B
        # choose leaving var
        leave_pos, leave_idx, theta = _select_leaving_variable(invA_B, A, b, enter, B)
        if leave_pos is None:
            return 'unbounded', None, None
        # pivot
        B, N = _pivot(B, N, enter, leave_pos)
        if verbose:
            print(f"Iter {it}: enter={enter}, leave={leave_idx}, theta={theta:.6g}")
    raise RuntimeError("Simplex: превышено макс. число итераций")

def two_phase_simplex(A_in, b_in, c_in, verbose=False):
    """
    Двухфазный симплекс:
    Phase I: добавить искусственные переменные для каждой строки, минимизировать их сумму.
    Phase II: если feasible, запустить simplex_max для исходной цели.
    Возвращает (status, x_opt, B) где status in {'optimal', 'infeasible', 'unbounded'}
    """
    A, b = _prepare_two_phase(A_in, b_in)
    m, n = A.shape
    # Phase I
    A_phase, b_phase, c_phase_dummy, B_phase = _simplex_tableau_from_phaseI(A, b, np.zeros(n))
    total_vars = A_phase.shape[1]  # n + m
    # Phase I objective: minimize sum of artificial vars => maximize -sum(ai)
    c_phase_obj = np.zeros(total_vars)
    for j in B_phase:
        c_phase_obj[j] = -1.0  # maximize negative sum -> minimization
    # Now run simplex_max with this initial basis
    status1, x_phase, B = simplex_max(A_phase, b_phase, c_phase_obj, B_init=B_phase, verbose=verbose)
    if status1 != 'optimal':
        # если не удалось найти оптимум Phase I — задача либо неограничена по искусст.переменным (не должно случаться), либо что-то пошло не так
        return 'infeasible', None, None
    # Check Phase I objective value (sum of artificial) should be ~0
    obj_phase_value = c_phase_obj @ x_phase
    if obj_phase_value < -EPS:  # помним: мы максимизировали -sum(ai). Значение ~= 0 означает sum(ai)=0
        # значит сумма искусственных > 0 => исходная система несовместна
        if verbose:
            print("Phase I: infeasible (sum of artificials > 0)")
        return 'infeasible', None, None
    # Для Phase II: нужно получить базис B без искусственных переменных.
    # Если в B остались искусственные переменные, попытаемся заменить их (по технике двухфазного метода).
    # Удаляем из системы искусственные столбцы и запускаем simplex с исходной целевой функцией.
    n_orig = n
    A2 = A_phase[:, :n_orig].copy()
    c2 = c_in.copy().astype(float)
    # Попробуем скорректировать B: если в B есть индексы >= n_orig (искусственные), заменим их
    B = list(B)
    for i, bi in enumerate(B):
        if bi >= n_orig:
            # ищем небазисный j, такой что столбец j линейно независим и можно заменить
            replaced = False
            for j in range(n_orig):
                if j not in B:
                    # проверим, можно ли сделать замену: элемент invA_B * a_j на позиции i != 0
                    # вычислим инверсию текущей B (включая искусственные) в A_phase и посмотрим
                    try:
                        _, inv_full = _compute_basic_solution(A_phase, b_phase, B)
                    except RuntimeError:
                        continue
                    a_j_full = A_phase[:, j]
                    d = inv_full @ a_j_full
                    if abs(d[i]) > EPS:
                        # выполнится правило замены
                        B[i] = j
                        replaced = True
                        break
            if not replaced:
                # Если заменить не удалось, это означает, что соответствующее уравнение является комбинацией других — это редкий случай
                # просто удалим столбец искусственной переменной (существует доп. логика в полном реализации)
                pass
    # убедимся, что B содержит только индексы < n_orig. Если нет, попытка удалить искусственные:
    B = [bi for bi in B if bi < n_orig]
    # если базис меньше m (строк), дополним какими-нибудь не базисными (обычно добавляют свободные переменные если возможно)
    all_indices = list(range(n_orig))
    for j in all_indices:
        if len(B) >= m:
            break
        if j not in B:
            B.append(j)
    if len(B) != m:
        # на практике базис размера m обязателен, но если не может быть сформирован — ошибка
        raise RuntimeError("Не удалось сформировать базис для Phase II")
    # Запускаем Phase II simplex с исходной целевой функцией
    status2, x_opt, B_opt = simplex_max(A2, b, c2, B_init=B, verbose=verbose)
    if status2 == 'optimal':
        # возвращаем решение (вектора длины n_orig)
        return 'optimal', x_opt[:n_orig], B_opt
    elif status2 == 'unbounded':
        return 'unbounded', None, None
    else:
        return 'infeasible', None, None

#
# ------------- Построение отсекающего ограничения Гомори -------------
#

def gomory_cut_from_solution(A, b, c, x, B):
    """
    Даны: A, b, c, оптимальный базисный план x и соответствующий базис B (список индексов длины m).
    Если x содержит дробные компоненты — строим одно отсекающее ограничение Гомори
    по шагам из формулировки.
    Возвращает: cut (coefficients over nonbasic variables, rhs fractional), информация.
    """
    m, n = A.shape
    # убеждаемся, что B длины m
    if len(B) != m:
        raise ValueError("Неправильный размер базиса B")
    # найдем индекс базисной переменной с дробной частью (берём первую или с наибольшей дробной частью)
    frac_parts = fractional_part(x[B])
    # если целых — ничего не делаем
    if np.all(frac_parts < EPS):
        return None, "solution_is_integer", None
    # выбираем k — позицию в B с максимальной дробной части
    k_pos = int(np.argmax(frac_parts))
    i_index = B[k_pos]  # индекс переменной в исходном x (1..n)
    # шаги: AB, AN
    A_B = A[:, B]
    N = [j for j in range(n) if j not in B]
    # упорядочим AN по возрастанию индексов (по условию)
    N.sort()
    A_N = A[:, N]
    # вычисляем A_B^{-1}
    invA_B = np.linalg.inv(A_B)
    # Q = A_B^{-1} * A_N
    Q = invA_B @ A_N
    # k-ая строка ℓ (k_pos по 0-индексу)
    row_l = Q[k_pos, :]
    # дробные части элементов строки
    frac_row = fractional_part(row_l)
    # правая сторона: дробная часть базисной переменной x_i
    rhs = fractional_part(x[i_index])
    # формируем ограничение: sum_p {ℓ_p} * (x_N)_p - s = {x_i}, s >= 0
    # Хотим вернуть в удобном виде: коэффициенты для всех исходных переменных x (небазисные имеют дробную часть, базисные — 0),
    # плюс дополнительная переменная s с коэф -1 и rhs = {x_i}
    coeffs_full = np.zeros(n)  # коэффициенты при исходных переменных
    for idx, p in enumerate(N):
        coeffs_full[p] = frac_row[idx]
    # s — новая переменная, покажем её явно
    s_coeff = -1.0
    return {
        'B_index_k_pos': k_pos,
        'B_index_variable': i_index,
        'N_indices': N,
        'coeffs_full': coeffs_full,
        's_coeff': s_coeff,
        'rhs_fraction': rhs,
        'frac_row': frac_row
    }, "cut_built", None

#
# ------------- Высокоуровневое управление (основной алгоритм лабораторной работы) -------------
#

def gomory_method(A, b, c, verbose=True):
    """
    Высокоуровневый метод:
    1) Двухфазный симплекс для LP (без целочисленности).
    2) Если infeasible/unbounded -> сообщаем.
    3) Если оптимальный и целочислен -> возвращаем решение.
    4) Иначе строим Gomory cut и возвращаем его (один шаг).
    Примечание: Реальная итеративная процедура добавления отсеков и повторного решения
    не реализована полностью — по заданию требуется построить одно отсекающее ограничение,
    либо вернуть оптимальный целочисленный план.
    """
    if verbose:
        print("Шаг 1. Решаем непрерывную версию задачи (двухфазный симплекс).")
    status, x_lp, B = two_phase_simplex(A, b, c, verbose=verbose)
    if status == 'infeasible':
        return {'status': 'infeasible_or_unbounded', 'message': 'Задача (LP) несовместна (или Phase I показал невозможность)'}
    if status == 'unbounded':
        return {'status': 'infeasible_or_unbounded', 'message': 'Целевая функция неограничена сверху на множестве допустимых планов'}
    # status == 'optimal'
    if verbose:
        print("Шаг 2/3. Найден оптимальный план LP (без целочисленности).")
        print_vector("x_LP", x_lp)
        print("Базис B (индексы):", B)
    # проверим целочисленность
    if _is_integer_vector(x_lp):
        if verbose:
            print("Шаг 3. План целочисленный — это оптимальное решение DP.")
        return {'status': 'integer_optimal', 'x': np.round(x_lp).astype(int), 'B': B}
    # иначе строим отсекающую плоскость Гомори
    if verbose:
        print("Шаг 4..11. План содержит дробные компоненты — строим отсекающее ограничение Гомори.")
    cut_info, msg, _ = gomory_cut_from_solution(A, b, c, x_lp, B)
    if msg == "solution_is_integer":
        # на всякий случай (но мы уже проверяли)
        return {'status': 'integer_optimal', 'x': np.round(x_lp).astype(int), 'B': B}
    if msg == "cut_built":
        # выведем в читаемом виде
        if verbose:
            print(f"Выбран базисный индекс (k-по счёту в B): {cut_info['B_index_k_pos']} (var index = {cut_info['B_index_variable']})")
            print("Небазисные индексы N (возрастающие):", cut_info['N_indices'])
            print("Дробные части строки ℓ (по небазисным столбцам):", np.array2string(cut_info['frac_row'], formatter={'float_kind':lambda x: f'{x:.6g}'}))
            print("Правая часть (дробная часть соответствующей базисной переменной):", cut_info['rhs_fraction'])
            # Печатаем само ограничение в форме: sum_p {ℓ_p} x_{N_p} - s = {x_i}
            terms = []
            for idx in cut_info['N_indices']:
                coef = cut_info['coeffs_full'][idx]
                if abs(coef) > EPS:
                    terms.append(f"{coef:.6g}*x_{idx+1}")
            lhs = " + ".join(terms) if terms else "0"
            lhs = lhs + f" {cut_info['s_coeff']:.6g}*s"
            print("Отсекающее ограничение Гомори (ввод новой переменной s >= 0):")
            print(f"    {lhs} = {cut_info['rhs_fraction']:.6g}")
        return {'status': 'gomory_cut', 'cut': cut_info, 'x_lp': x_lp, 'B': B}
    # fallback
    return {'status': 'error', 'message': 'Не удалось построить отсекающее ограничение'}

#
# ------------- Пример (тот, что приведён в задании) -------------
#

def example_from_statement():
    # Данные из примера в задании
    # Maximize x2
    # 3x1 + 2x2 + x3 = 6
    # -3x1 + 2x2 + x4 = 0
    # x >= 0
    A = np.array([[3.0, 2.0, 1.0, 0.0],
                  [-3.0,2.0, 0.0, 1.0]])
    b = np.array([6.0, 0.0])
    c = np.array([0.0, 1.0, 0.0, 0.0])  # максимизировать x2
    print("=== Пример из формулировки ===")
    result = gomory_method(A, b, c, verbose=True)
    print("Результат:", result)
    if result['status'] == 'gomory_cut':
        cut = result['cut']
        # печать в векторной форме (коэффициенты для переменных x1..xn, s)
        coeffs = cut['coeffs_full']
        rhs = cut['rhs_fraction']
        s_coef = cut['s_coeff']
        print("\nКоэффициенты отсекающего ограничения (включая s):")
        print_vector("coeffs_x", coeffs)
        print("coef_s = ", s_coef)
        print("rhs = ", rhs)

if __name__ == "__main__":
    example_from_statement()

