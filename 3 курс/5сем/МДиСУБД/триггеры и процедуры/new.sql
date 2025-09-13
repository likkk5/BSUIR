CREATE OR REPLACE PROCEDURE get_available_rooms(
    p_check_in_date DATE,
    p_check_out_date DATE
)
LANGUAGE plpgsql
AS $$
BEGIN
    -- Создаем временную таблицу для хранения доступных комнат
    CREATE TEMP TABLE temp_available_rooms AS
    SELECT room_number, room_type
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

CREATE OR REPLACE PROCEDURE cancel_reservation(p_reservation_id INT, p_guest_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_room_number VARCHAR;
BEGIN
    -- Проверяем, принадлежит ли бронирование указанному гостю
    IF NOT EXISTS (
        SELECT 1
        FROM reservation
        WHERE id = p_reservation_id AND guest_id = p_guest_id
    ) THEN
        RAISE EXCEPTION 'Reservation with ID % does not belong to guest with ID %.', p_reservation_id, p_guest_id;
    END IF;

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
DROP TRIGGER trigger_free_room_on_reservation_deletion ON reservation;