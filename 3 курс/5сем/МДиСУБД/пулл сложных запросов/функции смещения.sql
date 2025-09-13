-- Функции смещения
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
