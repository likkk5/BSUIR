-- Запросы с несколькими условиями (Логические операторы WHERE с AND, OR, NOT позволяют объединить несколько условий) 

-- Запрос на выбор гостей, проживающих LA и имеющих заполненный паспортный номер
SELECT id, passport_number, residence
FROM guest
WHERE residence LIKE '%Los Angeles, USA%' AND passport_number IS NOT NULL;

-- Запрос на выбор доступных номеров типа "Suite" или "Double"
SELECT room_number, room_type, cost_for_night
FROM room
WHERE (room_type = 'Suite' OR room_type = 'Double') AND room_status = 'Available';

-- Запрос на подтвержденные бронирования, исключая гостей с ID от 5 до 15
SELECT id, reservation_date, reservation_status
FROM reservation
WHERE reservation_status = 'Confirmed' AND NOT guest_id BETWEEN 5 AND 15;