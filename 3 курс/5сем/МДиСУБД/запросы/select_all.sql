SELECT * FROM feedback;
SELECT * FROM guest;
SELECT * FROM notification;
SELECT * FROM "order";
SELECT * FROM promocode;
SELECT * FROM reservation;
SELECT * FROM reservation_promocodes;
SELECT * FROM roles;
SELECT * FROM room;
SELECT * FROM service;
SELECT * FROM service_in_order;
SELECT * FROM "user";
SELECT first_name, last_name FROM "user";

SELECT * FROM room WHERE room_status = 'Available';
SELECT * FROM room WHERE room_type = 'Double' AND room_status = 'Available';
SELECT * FROM room WHERE room_type = 'Double' OR room_status = 'Available';
SELECT * FROM room WHERE room_status NOT IN ('Available');

SELECT * FROM feedback WHERE rating >= 4;
SELECT * FROM feedback WHERE rating > 4;
SELECT * FROM promocode WHERE promocode_status = TRUE;

SELECT COUNT(*) FROM reservation WHERE guest_id = 3;

SELECT first_name, last_name FROM "user" WHERE email LIKE '%@gmail.com';

SELECT * FROM room WHERE id IN(1,3);

SELECT * FROM guest WHERE residence = 'Los Angeles, USA';

SELECT * FROM reservation WHERE check_out_date BETWEEN '2024-10-14 00:00:00' AND '2024-10-15 23:59:59';
