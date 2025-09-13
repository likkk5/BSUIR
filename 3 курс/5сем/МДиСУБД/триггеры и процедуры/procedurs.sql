--1)
CREATE OR REPLACE PROCEDURE add_reservation(
    p_guest_id INT, --объявление переменных
    p_room_number VARCHAR,
    p_check_in_date DATE,
    p_check_out_date DATE,
    p_cost NUMERIC
)
LANGUAGE plpgsql --язык с блочной структурой(declare, begin, end)
AS $$
BEGIN --объявление
    -- Проверяем доступность комнаты
    IF EXISTS (
        SELECT 1 
        FROM reservation
        WHERE room_number = p_room_number
          AND (p_check_in_date BETWEEN check_in_date AND check_out_date
               OR p_check_out_date BETWEEN check_in_date AND check_out_date)
    ) THEN
        RAISE EXCEPTION 'The room is already booked for the selected dates.';
    END IF;

    -- Добавляем новое бронирование
    INSERT INTO reservation (guest_id, room_number, check_in_date, check_out_date, cost, reservation_date, reservation_status)
    VALUES (p_guest_id, p_room_number, p_check_in_date, p_check_out_date, p_cost, NOW(), 'Pending');

    -- Обновляем статус комнаты
    UPDATE room
    SET room_status = 'Occupied'
    WHERE room_number = p_room_number;

    RAISE NOTICE 'Reservation added successfully for room %', p_room_number;
END; --метка
$$;
-- Добавляем бронирование для доступной комнаты (№5).
CALL add_reservation(3, '5', (NOW() + INTERVAL '1 day')::DATE, (NOW() + INTERVAL '4 days')::DATE, 300.00);

--2) Пересчитывает стоимость заказа на основе услуг, связанных с заказом.
CREATE OR REPLACE PROCEDURE recalculate_order_cost(p_order_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_new_cost NUMERIC;
BEGIN
    -- Пересчитываем и обновляем стоимость заказа
    UPDATE "order"
    SET cost = (
        SELECT COALESCE(SUM(service.cost), 0)
        FROM service_in_order
        JOIN service ON service.id = service_in_order.service_id
        WHERE service_in_order.order_id = p_order_id
    )
    WHERE id = p_order_id;

    -- Получаем новую стоимость заказа после обновления
    SELECT cost INTO v_new_cost
    FROM "order"
    WHERE id = p_order_id;

    -- Выводим информацию о пересчитанной стоимости
    RAISE NOTICE 'Order cost recalculated for order ID %: New cost is %', p_order_id, v_new_cost;
END;
$$;

-- Добавляем услугу к существующему заказу ID 1.
INSERT INTO service_in_order (service_id, order_id, employee_id, amount)
VALUES (3, 1, 2, 1); -- Услуга ID 3 (Gym Access).

-- Пересчитываем стоимость заказа ID 1.
CALL recalculate_order_cost(1);

--3)
CREATE OR REPLACE PROCEDURE get_available_rooms(
    p_check_in_date DATE,
    p_check_out_date DATE
)
LANGUAGE plpgsql
AS $$
BEGIN
    -- Выводим список доступных комнат
    PERFORM room_number, room_type
    FROM room
    WHERE room_status = 'Available'
      AND NOT EXISTS (
          SELECT 1
          FROM reservation
          WHERE room.room_number = reservation.room_number
            AND (p_check_in_date BETWEEN check_in_date AND check_out_date
                 OR p_check_out_date BETWEEN check_in_date AND check_out_date)
      );

    RAISE NOTICE 'Available rooms retrieved successfully for dates % to %', p_check_in_date, p_check_out_date;
END;
$$;

CALL get_available_rooms((NOW() + INTERVAL '1 day')::DATE, (NOW() + INTERVAL '4 days')::DATE);

--4)
CREATE OR REPLACE PROCEDURE add_order(
    p_reservation_id INT,
    p_service_ids INT[], 
    p_amounts INT[],  
    p_employee_id INT,
    OUT p_order_id INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_service_id INT;
    v_amount INT;
    v_index INT;
BEGIN
   
    INSERT INTO "order" (reservation_id, cost, order_status, order_datetime, employee_id)
    VALUES (p_reservation_id, 0, 'Pending', NOW(), p_employee_id) 
    RETURNING id INTO p_order_id;

    -- Добавляем услуги к заказу с указанием количества каждой услуги
    v_index := 1;
    FOREACH v_service_id IN ARRAY p_service_ids LOOP
        v_amount := p_amounts[v_index];

        INSERT INTO service_in_order (order_id, service_id, employee_id, amount)
        VALUES (p_order_id, v_service_id, p_employee_id, v_amount); 
       
        v_index := v_index + 1; 
    END LOOP;

    CALL recalculate_order_cost(p_order_id);

    RAISE NOTICE 'Order added successfully with ID %', p_order_id;
END;
$$;

-- Создаем заказ для бронирования ID 2 с услугами ID 1 и 2, и employee_id = 1, и количеством 1 для каждой услуги
CALL add_order(2, ARRAY[1, 2], ARRAY[1, 1], 1, NULL);


--5)
CREATE OR REPLACE PROCEDURE get_avg_cost_by_room_type()
LANGUAGE plpgsql
AS $$
DECLARE
    v_room_type TEXT;
    v_avg_cost NUMERIC;
BEGIN
    -- Проходим по каждому типу комнаты
    FOR v_room_type, v_avg_cost IN
        SELECT room_type, AVG(cost)
        FROM reservation
        JOIN room ON reservation.room_number = room.room_number
        GROUP BY room_type
    LOOP
        -- Выводим среднюю стоимость для каждого типа комнаты
        RAISE NOTICE 'Room type: %, Average cost: %', v_room_type, v_avg_cost;
    END LOOP;

    RAISE NOTICE 'Average cost by room type retrieved successfully.';
END;
$$;

-- Вызов процедуры
CALL get_avg_cost_by_room_type();

--6)
CREATE OR REPLACE PROCEDURE cancel_reservation(p_reservation_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_room_number VARCHAR;
BEGIN
    -- Получаем номер комнаты, связанный с бронированием
    SELECT room_number INTO v_room_number
    FROM reservation
    WHERE id = p_reservation_id;

    -- Удаляем бронирование
    DELETE FROM reservation
    WHERE id = p_reservation_id;

    -- Обновляем статус комнаты
    UPDATE room
    SET room_status = 'Available'
    WHERE room_number = v_room_number;

    RAISE NOTICE 'Reservation with ID % canceled and room % is now available.', p_reservation_id, v_room_number;
END;
$$;

-- Отменяем бронирование.
CALL cancel_reservation(4);

--7)
CREATE OR REPLACE PROCEDURE get_guests_in_room(
    p_room_number VARCHAR,
    p_start_date DATE,
    p_end_date DATE
)
LANGUAGE plpgsql
AS $$
BEGIN
    -- Выводим список гостей
    PERFORM guest.id, guest.passport_number, "user".first_name, "user".last_name
    FROM guest
    JOIN reservation ON guest.id = reservation.guest_id
    JOIN "user" ON guest.user_id = "user".id
    WHERE reservation.room_number = p_room_number
      AND reservation.check_in_date >= p_start_date
      AND reservation.check_out_date <= p_end_date;

    RAISE NOTICE 'Guests retrieved for room % between % and %', p_room_number, p_start_date, p_end_date;
END;
$$;

-- Получаем гостей, проживавших в комнате в течение определенного времени.
CALL get_guests_in_room('1', (NOW() - INTERVAL '10 days')::DATE, NOW()::DATE);

SELECT column_name, data_type
FROM information_schema.columns
WHERE table_name = 'reservation' AND column_name = 'room_number';

SELECT column_name, data_type
FROM information_schema.columns
WHERE table_name = 'room' AND column_name = 'room_number';
