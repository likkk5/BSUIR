-- EXISTS для проверки существования связей

-- Выбор номеров, для которых существует хотя бы одно бронирование
SELECT room_number, room_type
FROM room
WHERE EXISTS (
    SELECT 1
    FROM reservation
    WHERE reservation.room_number = room.room_number
);
ALTER TABLE reservation
ALTER COLUMN room_number TYPE VARCHAR(10);

-- Список номеров, для которых нет активных заказов
SELECT *
FROM room
WHERE NOT EXISTS (
    SELECT *
    FROM reservation
    WHERE reservation.room_number = room.room_number
);
-- Список гостей, которые оставили хотя бы один отзыв
SELECT *
FROM guest
WHERE EXISTS (
    SELECT *
    FROM feedback
    WHERE feedback.guest_id = guest.id
);
-- IN
-- Услуги, которые были заказаны
SELECT *
FROM service
WHERE id IN (SELECT service_id FROM service_in_order);
-- Номера с промокодами
SELECT *
FROM room
WHERE room_number IN (SELECT room_number FROM reservation WHERE EXISTS (
    SELECT *
    FROM reservation_promocodes
    WHERE reservation_promocodes.reservation_id = reservation.id
));

