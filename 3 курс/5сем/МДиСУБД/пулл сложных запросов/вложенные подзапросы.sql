-- Запросы с вложенными конструкциями. Вложенные подзапросы -  не зависят от главного запроса. Их можно выполнить заранее один раз и запомнить результат

-- Коррелирующие(связывающие) подзапросы - выполняются по одному разу для каждой из строк внешнего запроса.(таблица из внешнего запроса используется во внутреннем подзапросе)
-- Список отзывов с датой и логином гостя
SELECT 
    feedback.feedback_text AS FeedbackText,
    feedback.feedback_datetime AS FeedbackDate,
    (SELECT login FROM "user" WHERE "user".id = (SELECT user_id FROM guest WHERE guest.id = feedback.guest_id)) AS GuestLogin
FROM 
    feedback;
	
-- Фильтр номеров, чья стоимость выше средней стоимости по типу номера
SELECT 
    room_number, 
    room_type, 
    cost_for_night,
    (SELECT AVG(cost_for_night) 
     FROM room AS r 
     WHERE r.room_type = room.room_type) AS avg_cost_for_type
FROM 
    room
WHERE 
    cost_for_night > 
        (SELECT AVG(cost_for_night) 
         FROM room AS r 
         WHERE r.room_type = room.room_type);
		 
--Получение имени и роли сотрудника, ответственного за заказ
SELECT 
    (SELECT first_name || ' ' || last_name 
     FROM "user" 
     WHERE "user".id = "order".employee_id) AS EmployeeName,
    (SELECT role_name 
     FROM roles 
     WHERE roles.id = (SELECT role_id FROM "user" WHERE "user".id = "order".employee_id)) AS Roles
FROM 
    "order";
-- Получение информации о госте и его заказах
SELECT 
    (SELECT first_name || ' ' || last_name 
     FROM "user" 
     WHERE "user".id = guest.user_id) AS GuestName,
    (SELECT room_number 
     FROM room 
     WHERE room.room_number = reservation.room_number) AS RoomNumber,
    (SELECT room_status 
     FROM room 
     WHERE room.room_number = reservation.room_number) AS RoomStatus,
    reservation_status AS ReservationStatus
FROM 
    reservation
JOIN 
    guest ON reservation.guest_id = guest.id;

-- Подзапрос для выбора бронирований с общей стоимостью выше средней стоимости услуги 
SELECT reservation.id, reservation.reservation_date, reservation.cost,
       (SELECT AVG(service.cost)
        FROM service
        JOIN service_in_order ON service.id = service_in_order.service_id) AS avg_service_cost
FROM reservation
WHERE reservation.cost > 
      (SELECT AVG(cost) FROM service);
	  
-- Запрос для получения данных о гостях с наибольшим количеством бронирований
SELECT guest.id, 
       "user".first_name || ' ' || "user".last_name AS full_name,  
       COUNT(reservation.id) AS reservation_count
FROM guest
JOIN reservation ON guest.id = reservation.guest_id
JOIN "user" ON guest.user_id = "user".id  -- Связываем с таблицей "user" через user_id
GROUP BY guest.id, "user".first_name, "user".last_name  -- Группируем по id гостя и его полному имени
ORDER BY reservation_count DESC;  -- Сортируем по количеству резервирований

-- Не коррелирующие подзапросы. Выборка с использованием агрегатных функций
SELECT guest_id, rating
FROM feedback
WHERE rating >= (SELECT AVG(rating) FROM feedback)

SELECT guest_id, rating
FROM feedback
WHERE rating = (SELECT MIN(rating) FROM feedback)

SELECT guest_id, rating
FROM feedback
WHERE rating = (SELECT MAX(rating) FROM feedback)

-- Некоррелирующий подзапрос для списка гостей, забронировавших номер с самой высокой стоимостью
SELECT guest.id, guest.passport_number, guest.residence
FROM guest
JOIN reservation ON guest.id = reservation.guest_id
WHERE reservation.room_number IN (
      SELECT room_number
      FROM room
      WHERE cost_for_night = (SELECT MAX(cost_for_night) FROM room) 
);

--  Классификация вложенных подзапросов
--  По количеству строк:
--  однострочные - гарантированно возвращают одну строку, с ними используют "однострочные операторы сравнения" (арифметические знаки сравнения)
--  многострочные -  с ними используют "многострочные" операторы сравнения (IN сущ в списке, ANY, ALL)

--  По виду:
--  многостолбцовые - возвращают несколько столбцов
	--  попарное: два поля у одного объекта сравниваются с теми же полями у другого объекта
	--  не попарное: берется два поля у одного объекта, первое поле сравнивается с полем первого
	--  объекта, второе поле - с полем второго объекта
--  коррелированные - выполняются по одному разу для каждой из строк внешнего запроса.
--  вложенные - не зависят от главного запроса. Их можно выполнить заранее один раз и запомнить
--  результат