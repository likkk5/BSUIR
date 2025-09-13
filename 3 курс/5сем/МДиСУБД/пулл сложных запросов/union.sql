-- UNION для объединения результатов запросов(дублирующиеся строки исключены, кроме UNION ALL)

-- Доступные и занятые комнаты в одном списке
SELECT room_number, room_type, room_status
FROM room
WHERE room_status = 'Available'
UNION
SELECT room_number, room_type, room_status
FROM room
WHERE room_status = 'Occupied';

-- Объединение всех услуг с минимальной стоимостью
SELECT name, cost
FROM service
WHERE cost < 100
UNION
SELECT name, cost
FROM service
WHERE cost >= 100 AND cost < 200;

-- Объединение списков всех гостей и сотрудников
SELECT CONCAT("user".first_name, ' ', "user".last_name) AS full_name
FROM guest
JOIN "user" ON guest.user_id = "user".id
UNION
SELECT CONCAT("user".first_name, ' ', "user".last_name) AS full_name
FROM "user"
WHERE "user".role_id = (SELECT id FROM roles WHERE role_name = 'Employee');
--Объединение идентификаторов гостей и сотрудников
SELECT id AS UserID 
FROM guest
UNION ALL
SELECT id AS UserID
FROM "user";
-- Объединение отзывов по разным рейтингам
SELECT feedback_text, rating + rating * 0.1 AS AdjustedRating
FROM feedback
WHERE rating <= 3
UNION
SELECT feedback_text, rating + rating * 0.3 AS AdjustedRating
FROM feedback
WHERE rating > 3;
--Объединение информации о заказах и услугах
SELECT id AS ItemID, cost AS ItemCost, 'Order' AS ItemType
FROM "order"
UNION
SELECT id AS ItemID, cost AS ItemCost, 'Service' AS ItemType
FROM service
ORDER BY ItemCost;
