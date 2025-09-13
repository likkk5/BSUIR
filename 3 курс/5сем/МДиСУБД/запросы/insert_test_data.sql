INSERT INTO role (role_name) 
VALUES 
('Admin'), 
('Employee'), 
('Guest');

INSERT INTO "user" (first_name, last_name, login, password, role_id, phone_number, email) 
VALUES 
('Ksusha', 'Lishyk', 'admin', 'Passw0rd!', 1, '1234567890', 'admin@gmail.com'),  -- Админ
('Emily', 'Johnson', 'ejohnson', 'password123', 2, '1234567890', 'emily.johnson@gmail.com'),  -- Сотрудник
('James', 'Williams', 'jwilliams', 'password456', 2, '0987654321', 'james.williams@gmail.com'),  -- Сотрудник
('Olivia', 'Brown', 'obrown', 'password789', 3, '1122334455', 'olivia.brown@gmail.com'),  -- Гость
('Sophia', 'Davis', 'sdavis', 'password321', 3, '2233445566', 'sophia.davis@gmail.com');  -- Гость

INSERT INTO guest (user_id, passport_number, residence) 
VALUES 
(4, 'XY1234567', 'Los Angeles, USA'),  -- Гость 1
(4, 'YX7654321', 'London, UK'),        -- Гость 1
(5, 'PQ2345678', 'Paris, France');      -- Гость 2

INSERT INTO room (room_type, cost_for_night, room_status, photo) 
VALUES 
('Single', 100.00, 'Available', NULL),
('Double', 150.00, 'Occupied', NULL),
('Suite', 300.00, 'Available', NULL),
('Single', 110.00, 'Occupied', NULL),
('Double', 160.00, 'Available', NULL);

INSERT INTO reservation (reservation_date, check_in_date, check_out_date, reservation_status, room_number, guest_id, cost) 
VALUES 
(NOW(), NOW() + INTERVAL '1 day', NOW() + INTERVAL '3 days', 'Confirmed', 1, 1, 300.00),
(NOW(), NOW() + INTERVAL '2 days', NOW() + INTERVAL '6 days', 'Confirmed', 2, 2, 900.00),
(NOW(), NOW() + INTERVAL '1 day', NOW() + INTERVAL '4 days', 'Checked-in', 3, 3, 1200.00);

INSERT INTO service (name, cost, photo) 
VALUES 
('Room Service', 50.00, NULL),
('Spa', 120.00, NULL),
('Gym Access', 30.00, NULL),
('Laundry', 40.00, NULL),
('Breakfast Buffet', 25.00, NULL);

INSERT INTO feedback (guest_id, feedback_datetime, feedback_text, rating) 
VALUES 
(1, NOW(), 'Fantastic stay, very clean and comfortable!', 5),
(2, NOW(), 'Service was good but room could be cleaner.', 3),
(3, NOW(), 'Loved the spa and gym access, will return!', 4);

INSERT INTO "order" (order_datetime, reservation_id, order_status, employee_id, cost) 
VALUES 
(NOW(), 1, 'Completed', 2, 150.00),
(NOW(), 2, 'Pending', 3, 100.00),
(NOW(), 3, 'Processing', 2, 200.00),
(NOW(), 3, 'Canceled', 3, 200.00);

INSERT INTO notification (notification_datetime, notification_text, order_id) 
VALUES 
(NOW(), 'Your order has been successfully completed', 1),
(NOW(), 'Your order is pending, awaiting confirmation', 2),
(NOW(), 'Order is being processed', 3);

INSERT INTO service_in_order (service_id, order_id, employee_id, amount) 
VALUES 
(1, 1, 2, 1),
(2, 2, 3, 1),
(3, 3, 3, 1),
(4, 1, 2, 2),
(5, 2, 3, 3);

INSERT INTO promocode (code, promocode_status, sale_type, sale_amount, promocode_start_date, promocode_expiration_date) 
VALUES 
('SUMMER2024', TRUE, 'Percentage', 20.00, NOW(), NOW() + INTERVAL '6 months'),
('WINTER2024', TRUE, 'Fixed', 50.00, NOW(), NOW() + INTERVAL '1 year'),
('AUTUMN2024', FALSE, 'Percentage', 10.00, NOW() - INTERVAL '3 months', NOW() + INTERVAL '2 months');

INSERT INTO reservation_promocodes (promocode_id, reservation_id, quantity) 
VALUES 
(1, 1, 1),
(2, 2, 1),
(3, 3, 1);

INSERT INTO feedback (guest_id, feedback_datetime, feedback_text, rating) VALUES (1, NOW(), 'Very clean and comfortable rooms!', 5);

