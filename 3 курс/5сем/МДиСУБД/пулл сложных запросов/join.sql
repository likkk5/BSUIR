-- JOIN-запросы для объединения данных

-- Неявное соединение таблиц
SELECT 
    "order".id AS OrderID,
    guest.id AS GuestID,
    "user".first_name || ' ' || "user".last_name AS GuestName,
    feedback.feedback_text AS FeedbackText
FROM 
    "order", guest, "user", feedback
WHERE 
    "order".reservation_id = guest.id
    AND guest.user_id = "user".id
    AND feedback.guest_id = guest.id;

-- ON Используется для явного указания условия объединения двух таблиц, позволяет объединять таблицы по различным критериям
-- INNER JOIN(внутреннее соединение) для получения всех резерваций с информацией о гостях и комнатах
SELECT 
    reservation.id AS reservation_id, 
    guest.passport_number, 
    room.room_type, 
    reservation.check_in_date, 
    reservation.check_out_date
FROM 
    reservation
INNER JOIN 
    guest ON reservation.guest_id = guest.id
INNER JOIN 
    room ON reservation.room_number = room.room_number; --условия объединения
	
SELECT 
    feedback.feedback_text AS FeedbackText,
    feedback.feedback_datetime AS FeedbackDate,
    (SELECT login FROM "user" WHERE "user".id = (SELECT user_id FROM guest WHERE guest.id = feedback.guest_id)) AS GuestLogin
FROM 
    feedback;
	


SELECT 
    feedback.feedback_text AS FeedbackText,
    feedback.feedback_datetime AS FeedbackDate,
	"user".login AS guestlogin
FROM feedback

INNER JOIN guest ON guest.id = feedback.guest_id
INNER JOIN "user" ON "user".id = guest.user_id


-- INNER JOIN для списка всех заказов с информацией о госте и сотруднике
SELECT "order".id AS order_id, guest.passport_number, "user".first_name AS employee_name, "order".cost
FROM "order"
INNER JOIN guest ON "order".reservation_id = guest.id
INNER JOIN "user" ON "order".employee_id = "user".id;

-- LEFT JOIN для получения всех гостей и их резерваций, включая гостей без резерваций
-- OUTER+INNER
SELECT 
    guest.id AS guest_id, 
    CONCAT("user".first_name, ' ', "user".last_name) AS full_name, 
    reservation.id AS reservation_id
FROM 
    guest
LEFT JOIN 
    reservation ON guest.id = reservation.guest_id
JOIN 
    "user" ON guest.user_id = "user".id;

-- OUTER JOIN(возвращает строки, не имеющие соответсвия в другой таблице)
-- LEFT JOIN для получения всех услуг по каждому заказу, включая заказы без услуг
SELECT "order".id AS order_id, service.name AS service_name, service.cost
FROM "order"
LEFT JOIN service_in_order ON "order".id = service_in_order.order_id
LEFT JOIN service ON service_in_order.service_id = service.id;

-- RIGHT JOIN для получения всех комнат и информации о резервациях, включая комнаты без резерваций
SELECT 
    room.room_number, 
    room.room_type, 
    reservation.id AS reservation_id
FROM 
    room
RIGHT JOIN 
    reservation ON room.room_number = reservation.room_number;

-- FULL JOIN для получения всех услуг и заказов, включая заказы без услуг и услуги без заказов
SELECT 
    service.name AS service_name, 
    "order".id AS order_id, 
    "order".cost
FROM 
    service
FULL JOIN 
    service_in_order ON service.id = service_in_order.service_id
FULL JOIN 
    "order" ON service_in_order.order_id = "order".id;

-- CROSS JOIN для получения всех возможных комбинаций услуг и резерваций(декартово произведение двух таблиц, каждая строка из первой таблицы соединяется с каждой строкой из второй)
SELECT 
    service.name AS service_name, 
    reservation.id AS reservation_id
FROM 
    service
CROSS JOIN 
    reservation;

-- SELF JOIN для сравнения гостей по месту жительства в одной таблице
SELECT 
    g1.id AS guest_id_1, 
    g1.residence AS residence_1, 
    g2.id AS guest_id_2, 
    g2.residence AS residence_2
FROM 
    guest g1, guest g2
WHERE 
    g1.id <> g2.id AND g1.residence = g2.residence; --неравно

-- INNER JOIN(внутрнее соединение): Образует новую таблицу, в которой возвращает только те строки, которые имеют совпадения в обеих таблицах.
-- LEFT JOIN: Возвращает все строки из левой таблицы и соответствующие строки из правой. Если в правой таблице нет совпадений, возвращает NULL.
-- RIGHT JOIN: Возвращает все строки из правой таблицы и соответствующие строки из левой. Если в левой таблице нет совпадений, возвращает NULL.
-- FULL JOIN: Возвращает все строки из обеих таблиц, при этом для строк без совпадений возвращает NULL.
-- CROSS JOIN: Возвращает декартово произведение двух таблиц, то есть все возможные комбинации строк.
-- SELF JOIN: Используется для сравнения строк в одной таблице. объединяет таблицу с ее же копией.
