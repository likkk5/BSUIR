-- Пул запросов для получения сгруппированных данных(агрегатные функции используются совместно с группировкой, обрабатывают несколько строк и вычисляют одно значение)

-- Средняя стоимость бронирования по типу комнаты
SELECT room.room_type, AVG(reservation.cost) AS avg_reservation_cost
FROM reservation
JOIN room ON reservation.room_number = room.room_number
GROUP BY room.room_type;

-- GROUP BY + HAVING для бронирований с количеством услуг больше 1(сокращает кол-во строк в запросе с помощью их групппировки, в отличии от оконных функций)
SELECT reservation.id, COUNT(service_in_order.service_id) AS service_count
FROM reservation
JOIN service_in_order ON reservation.id = service_in_order.order_id
GROUP BY reservation.id
HAVING COUNT(service_in_order.service_id) > 1;

-- Фильтрация гостей с общим количеством резервирований больше или равно 1
SELECT guest.id AS guest_id, 
       CONCAT("user".first_name, ' ', "user".last_name) AS full_name, 
       COUNT(reservation.id) AS total_reservations
FROM guest
JOIN reservation ON guest.id = reservation.guest_id
JOIN "user" ON guest.user_id = "user".id
GROUP BY guest.id, "user".first_name, "user".last_name
HAVING COUNT(reservation.id) >= 1;

-- WHERE не работает с агригирующими функциями, используем HAVING