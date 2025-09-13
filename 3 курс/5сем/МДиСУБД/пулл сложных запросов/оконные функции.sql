-- Оконные функции-функция которая работает с выделенным набором строк(окном, партицией) и выполняет вычисление для этого набора строк в отдельном столбце
-- Партиции(окна из наборов строк)- набор строк, указанный для оконной функции по одному из стобцов или группе столбцов таблицы
-- 1. Агрегирующие
-- Информация о заказах, сгруппированная по гостю и статистика по стоимости
SELECT 
    "order".id AS OrderID,
    "order".reservation_id AS GuestID,
    "order".cost AS OrderCost,
    SUM("order".cost) OVER (PARTITION BY "order".reservation_id) AS TotalSpent,
    AVG("order".cost) OVER (PARTITION BY "order".reservation_id) AS AvgSpent,
    COUNT("order".cost) OVER (PARTITION BY "order".reservation_id) AS OrderCount,
    MIN("order".cost) OVER (PARTITION BY "order".reservation_id) AS MinSpent,
    MAX("order".cost) OVER (PARTITION BY "order".reservation_id) AS MaxSpent
FROM 
    "order"
JOIN 
    guest ON guest.id = "order".reservation_id; ---- ON Используется для явного указания условия объединения двух таблиц, позволяет объединять таблицы по различным критериям

-- Общее количество резерваций по типу комнаты
SELECT room.room_type, 
       COUNT(reservation.id) AS total_reservations
FROM reservation
JOIN room ON reservation.room_number = room.room_number
GROUP BY room.room_type;

-- Сумма всех резервирований по каждому гостю
SELECT guest.id AS guest_id, 
       CONCAT("user".first_name, ' ', "user".last_name) AS full_name, 
       SUM(reservation.cost) AS total_cost
FROM guest
JOIN reservation ON guest.id = reservation.guest_id
JOIN "user" ON guest.user_id = "user".id
GROUP BY guest.id, "user".first_name, "user".last_name;

-- Средняя стоимость бронирования по типу комнаты
SELECT room.room_type, AVG(reservation.cost) AS avg_reservation_cost
FROM reservation
JOIN room ON reservation.room_number = room.room_number
GROUP BY room.room_type;

-- 2. Ранжирующие
SELECT 
    "order".id AS OrderID,
    "order".reservation_id AS GuestID,
    "order".cost AS OrderCost,
    ROW_NUMBER() OVER (PARTITION BY "order".reservation_id ORDER BY "order".cost) AS OrderRowNumber, -- независимо от повт значений --ORDER BY(условие, по которому происходит ранжирование, по умолчанию сортировка по возрастанию)
    RANK() OVER (PARTITION BY "order".reservation_id ORDER BY "order".cost) AS OrderRank, -- с пропуском, одинаковый ранг для повторяющихся значений
    DENSE_RANK() OVER (PARTITION BY "order".reservation_id ORDER BY "order".cost) AS OrderDenseRank, -- без пропуска
    NTILE(2) OVER (PARTITION BY "order".reservation_id ORDER BY "order".cost) AS OrderNtile,
    CUME_DIST() OVER (PARTITION BY "order".reservation_id ORDER BY "order".cost) AS OrderCumeDist
FROM 
    "order"
JOIN 
    guest ON guest.id = "order".reservation_id;
-- OrderRowNumber — порядковый номер заказа по стоимости для каждого гостя (начиная с наименьшего). Если несколько заказов имеют одинаковую стоимость, каждому присваивается уникальный порядковый номер.
-- OrderRank — ранг заказа по стоимости для каждого гостя, с пропуском в случае одинаковых значений. Если у гостя есть несколько заказов с одинаковой стоимостью, ранг повторяется, а следующие заказы получают ранг с пропуском.
-- OrderDenseRank — плотный ранг по стоимости для каждого гостя. В отличие от RANK, здесь не пропускаются ранги при одинаковых значениях стоимости.
-- OrderNtile(2) — разделение заказов каждого гостя на два равных набора (квартиль). Если у гостя есть несколько заказов, они будут распределены по двум группам в порядке возрастания стоимости.
-- OrderCumeDist — накопленное распределение, которое показывает долю заказов с меньшей или равной стоимостью для каждого гостя.

-- Ранжирование заказов по стоимости для каждого гостя
SELECT guest.id, guest.passport_number,
       "order".id AS order_id,
       "order".cost,
       RANK() OVER (PARTITION BY guest.id ORDER BY "order".cost DESC) AS order_rank
FROM guest
JOIN reservation ON guest.id = reservation.guest_id
JOIN "order" ON reservation.id = "order".reservation_id;

-- Подсчет резервирований с использованием оконных функций
SELECT reservation.id, 
       guest.id AS guest_id,
       COUNT(reservation.id) OVER (PARTITION BY guest.id) AS reservation_count
FROM reservation
JOIN guest ON reservation.guest_id = guest.id;

-- Средняя стоимость бронирования по гостю с использованием оконной функции
SELECT guest.id AS guest_id, 
       CONCAT("user".first_name, ' ', "user".last_name) AS full_name,
       AVG(reservation.cost) OVER (PARTITION BY guest.id) AS avg_cost
FROM guest
JOIN reservation ON guest.id = reservation.guest_id
JOIN "user" ON guest.user_id = "user".id;

-- Ранжирование гостей по общим затратам на резервирования
SELECT guest.id AS guest_id,
       CONCAT("user".first_name, ' ', "user".last_name) AS full_name,
       SUM(reservation.cost) AS total_spent,
       DENSE_RANK() OVER (ORDER BY SUM(reservation.cost) DESC) AS spending_rank
FROM guest
JOIN reservation ON guest.id = reservation.guest_id
JOIN "user" ON guest.user_id = "user".id
GROUP BY guest.id, "user".first_name, "user".last_name;

-- Разбивка гостей на 4 группы по количеству резервирований
SELECT guest.id AS guest_id,
       CONCAT("user".first_name, ' ', "user".last_name) AS full_name,
       COUNT(reservation.id) AS reservation_count,
       NTILE(4) OVER (ORDER BY COUNT(reservation.id) DESC) AS reservation_quartile
FROM guest
LEFT JOIN reservation ON guest.id = reservation.guest_id
JOIN "user" ON guest.user_id = "user".id
GROUP BY guest.id, "user".first_name, "user".last_name;

-- Присвоение уникального номера каждому заказу по дате
SELECT "order".id AS order_id,
       reservation.check_in_date,
       ROW_NUMBER() OVER (ORDER BY reservation.check_in_date) AS order_number
FROM "order"
JOIN reservation ON "order".reservation_id = reservation.id;

-- Кумулятивное распределение затрат по заказам
SELECT "order".id AS order_id,
       "order".cost,
       CUME_DIST() OVER (ORDER BY "order".cost) AS cumulative_distribution
FROM "order";

-- 3. Функции смещения - позволяют перемещаться по выделеной партиции таблицы обращаясь к пред\след значению строки или крайним значениям строк в партициии.
SELECT 
    "order".id AS OrderID,
    "order".reservation_id AS GuestID,
    "order".cost AS OrderCost,
    LAG("order".cost) OVER (PARTITION BY "order".reservation_id ORDER BY "order".id) AS PreviousCost, -- пред знач столбца
    LEAD("order".cost) OVER (PARTITION BY "order".reservation_id ORDER BY "order".id) AS NextCost,-- след
    FIRST_VALUE("order".cost) OVER (PARTITION BY "order".reservation_id ORDER BY "order".id) AS FirstOrderCost,
    LAST_VALUE("order".cost) OVER (PARTITION BY "order".reservation_id ORDER BY "order".id RANGE BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS LastOrderCost
FROM 
    "order"
JOIN 
    guest ON guest.id = "order".reservation_id;
-- Функции LAG и LEAD помогают посмотреть стоимость предыдущего и следующего заказа соответственно
-- FIRST_VALUE и LAST_VALUE возвращают стоимость первого и последнего заказа для каждого гостя, независимо от количества заказов.

-- Получение стоимости предыдущего бронирования для каждого гостя
SELECT guest.id AS guest_id,
       reservation.id AS reservation_id,
       reservation.cost,
       LAG(reservation.cost) OVER (PARTITION BY guest.id ORDER BY reservation.check_in_date) AS previous_cost
FROM reservation
JOIN guest ON reservation.guest_id = guest.id;

-- Получение стоимости следующего бронирования для каждого гостя
SELECT guest.id AS guest_id,
       reservation.id AS reservation_id,
       reservation.cost,
       LEAD(reservation.cost) OVER (PARTITION BY guest.id ORDER BY reservation.check_in_date) AS next_cost
FROM reservation
JOIN guest ON reservation.guest_id = guest.id;

-- Получение первой стоимости бронирования для каждого гостя
SELECT guest.id AS guest_id,
       reservation.id AS reservation_id,
       reservation.cost,
       FIRST_VALUE(reservation.cost) OVER (PARTITION BY guest.id ORDER BY reservation.check_in_date) AS first_booking_cost
FROM reservation
JOIN guest ON reservation.guest_id = guest.id;

-- Получение последней стоимости бронирования для каждого гостя
SELECT guest.id AS guest_id,
       reservation.id AS reservation_id,
       reservation.cost,
       LAST_VALUE(reservation.cost) OVER (PARTITION BY guest.id ORDER BY reservation.check_in_date 
                                           ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS last_booking_cost
FROM reservation
JOIN guest ON reservation.guest_id = guest.id;
