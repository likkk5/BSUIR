--1)
CREATE OR REPLACE FUNCTION recalculate_order_cost()
RETURNS TRIGGER AS $$ --тело функции должно быть строковой константой
BEGIN
    -- Пересчитываем стоимость заказа, включая все услуги
    UPDATE "order"
    SET cost = (
        SELECT COALESCE(SUM(service.cost), 0)
        FROM service_in_order
        JOIN service ON service.id = service_in_order.service_id
        WHERE service_in_order.order_id = NEW.order_id
    )
    WHERE id = NEW.order_id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_recalculate_order_cost
AFTER INSERT OR DELETE ON service_in_order
FOR EACH ROW --функция вызывается для каждой строки которая изменяется в рез события
EXECUTE FUNCTION recalculate_order_cost();

-- Добавляем услугу к заказу ID 2.
INSERT INTO service_in_order (service_id, order_id, employee_id, amount)
VALUES (4, 2, 3, 1); -- Услуга ID 4 (Laundry).
SELECT cost FROM "order" WHERE id = 2;

--2)
CREATE OR REPLACE FUNCTION update_room_status_on_reservation()
RETURNS TRIGGER AS $$
BEGIN
    -- Если добавлено новое бронирование, обновляем статус комнаты на "Занята"
    UPDATE room
    SET room_status = 'Occupied'
    WHERE room_number = NEW.room_number;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_room_status_on_reservation
AFTER INSERT ON reservation
FOR EACH ROW
EXECUTE FUNCTION update_room_status_on_reservation();
DROP TRIGGER trigger_update_room_status_on_reservation ON reservation;

-- Добавляем бронирование для комнаты.
INSERT INTO reservation (reservation_date, check_in_date, check_out_date, reservation_status, room_number, guest_id, cost)
VALUES (NOW(), NOW() + INTERVAL '2 days', NOW() + INTERVAL '6 days', 'Confirmed', '104', 3, 500.00);
SELECT * FROM room;

--3)
CREATE OR REPLACE FUNCTION free_room_on_reservation_deletion()
RETURNS TRIGGER AS $$
BEGIN
    -- Если бронирование удалено, проверяем, свободна ли комната
    UPDATE room
    SET room_status = 'Available'
    WHERE room_number = OLD.room_number;

    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_free_room_on_reservation_deletion
AFTER DELETE ON reservation
FOR EACH ROW
EXECUTE FUNCTION free_room_on_reservation_deletion();

-- Удаляем бронирование ID 2.
DELETE FROM reservation WHERE id = 2;
SELECT room_status FROM room WHERE room_number = '102';

--4)
CREATE OR REPLACE FUNCTION validate_reservation_dates()
RETURNS TRIGGER AS $$
BEGIN
    -- Проверяем, что дата заезда меньше даты выезда
    IF NEW.check_in_date >= NEW.check_out_date THEN
        RAISE EXCEPTION 'Check-in date must be earlier than check-out date.';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_validate_reservation_dates
BEFORE INSERT OR UPDATE ON reservation
FOR EACH ROW
EXECUTE FUNCTION validate_reservation_dates();

-- Неверное бронирование.
INSERT INTO reservation (reservation_date, check_in_date, check_out_date, reservation_status, room_number, guest_id, cost)
VALUES (NOW(), NOW() + INTERVAL '5 days', NOW() + INTERVAL '3 days', 'Confirmed', 3, 1, 300.00);

--5)
CREATE OR REPLACE FUNCTION update_order_status_on_payment()
RETURNS TRIGGER AS $$
BEGIN
    -- Если заказ полностью оплачен, обновляем статус
    IF NEW.order_status = 'Paid' THEN
        UPDATE "order"
        SET order_status = 'Completed'
        WHERE id = NEW.id;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_order_status_on_payment
AFTER UPDATE ON "order"
FOR EACH ROW
EXECUTE FUNCTION update_order_status_on_payment();
DROP TRIGGER trigger_update_order_status_on_payment ON "order";

-- Добавляем заказ со статусом оплаты "Pending".
INSERT INTO "order" (reservation_id, cost, order_status, order_datetime, employee_id)
VALUES (1, 500, 'Pending', NOW(),1);

-- Обновляем статус оплаты на "Paid".
UPDATE "order"
SET order_status = 'Paid'
WHERE id = (SELECT MAX(id) FROM "order");
SELECT order_status FROM "order";

--6)
CREATE OR REPLACE FUNCTION check_room_availability()
RETURNS TRIGGER AS $$
BEGIN
    -- Проверяем, свободна ли комната для бронирования
    IF EXISTS (
        SELECT 1 
        FROM reservation
        WHERE room_number = NEW.room_number 
          AND (NEW.check_in_date BETWEEN check_in_date AND check_out_date 
               OR NEW.check_out_date BETWEEN check_in_date AND check_out_date)
    ) THEN
        RAISE EXCEPTION 'The room is already booked for the selected dates.';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Добавляем бронирование для свободной комнаты.
INSERT INTO reservation (reservation_date, check_in_date, check_out_date, reservation_status, room_number, guest_id, cost)
VALUES (NOW(), NOW() + INTERVAL '1 day', NOW() + INTERVAL '4 days', 'Confirmed', 6, 2, 200.00);
-- Попробуем забронировать ту же комнату в те же даты.
INSERT INTO reservation (reservation_date, check_in_date, check_out_date, reservation_status, room_number, guest_id, cost)
VALUES (NOW(), NOW() + INTERVAL '2 days', NOW() + INTERVAL '3 days', 'Confirmed', 6, 3, 300.00);


CREATE TABLE action_log (
    id SERIAL PRIMARY KEY,
    action_type VARCHAR(50) NOT NULL,
    table_name VARCHAR(50) NOT NULL,
    record_id INT,
    action_timestamp TIMESTAMP DEFAULT NOW()
);

CREATE OR REPLACE FUNCTION log_action()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO action_log (action_type, table_name, record_id)
    VALUES (TG_OP, TG_TABLE_NAME, COALESCE(NEW.id, OLD.id));

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_log_feedback_action
AFTER INSERT OR UPDATE OR DELETE ON feedback
FOR EACH ROW
EXECUTE FUNCTION log_action();
DROP TRIGGER trigger_log_feedback_action ON feedback;

INSERT INTO feedback (guest_id, feedback_datetime, feedback_text, rating)
VALUES (3, NOW(), 'Good service!', 4);

UPDATE feedback
SET feedback_text = 'Excellent service!', rating = 5
WHERE id = (SELECT MAX(id) FROM feedback);

DELETE FROM feedback WHERE id = (SELECT MAX(id) FROM feedback);

CREATE TRIGGER trigger_log_reservation_action
AFTER INSERT OR UPDATE OR DELETE ON reservation
FOR EACH ROW
EXECUTE FUNCTION log_action();

INSERT INTO reservation (reservation_date, check_in_date, check_out_date, reservation_status, room_number, guest_id, cost)
VALUES (NOW(), NOW() + INTERVAL '1 day', NOW() + INTERVAL '4 days', 'Confirmed', '101', 3, 300.00);

UPDATE reservation
SET cost = 350.00
WHERE id = (SELECT MAX(id) FROM reservation);

DELETE FROM reservation WHERE id = (SELECT MAX(id) FROM reservation);

SELECT * FROM action_log ORDER BY action_timestamp DESC;
