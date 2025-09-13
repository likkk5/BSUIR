UPDATE room SET room_number = '101' WHERE id = 1;
UPDATE room SET room_number = '102' WHERE id = 2;
UPDATE room SET room_number = '103' WHERE id = 3;
UPDATE room SET room_number = '104' WHERE id = 4;
UPDATE room SET room_number = '105' WHERE id = 5;

UPDATE reservation SET room_number = '101' WHERE room_number = 1;
UPDATE reservation SET room_number = '102' WHERE room_number = 2;
UPDATE reservation SET room_number = '103' WHERE room_number = 3;

UPDATE reservation SET reservation_status = 'Checked-in' WHERE id = 1;
UPDATE reservation SET cost = cost * (1 - 50.00 / 100) WHERE id = 1;
