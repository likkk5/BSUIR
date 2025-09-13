-- CASE для условий в выборке

-- Классификация комнат по стоимости
SELECT room_number, room_type, cost_for_night,
       CASE
           WHEN cost_for_night < 100 THEN 'Economy'
           WHEN cost_for_night BETWEEN 100 AND 200 THEN 'Standard'
           ELSE 'Luxury'
       END AS category
FROM room;
--Использование CASE в SELECT
SELECT 
    guest.id AS GuestID,
    guest.passport_number AS PassportNumber,
    COUNT(reservation.id) AS OrderCount,
    CASE
        WHEN COUNT(reservation.id) = 0 THEN 'New'
        WHEN COUNT(reservation.id) BETWEEN 1 AND 3 THEN 'Regular'
        ELSE 'Frequent'
    END AS GuestCategory
FROM 
    guest
LEFT JOIN 
    reservation ON guest.id = reservation.guest_id
GROUP BY 
    guest.id, guest.passport_number;

--Использование CASE в UPDATE
UPDATE "order"
SET 
    order_status = CASE
        WHEN cost < 100 THEN 'Low'
        WHEN cost BETWEEN 100 AND 300 THEN 'Medium'
        ELSE 'High'
    END
WHERE cost IS NOT NULL;

UPDATE "order"
SET order_status = CASE
    WHEN reservation_id = 1 THEN 'Completed'
    WHEN reservation_id = 2 THEN 'Pending'
    WHEN reservation_id = 3 AND cost = 200.00 THEN 'Processing'
    WHEN reservation_id = 3 AND cost = 200.00 THEN 'Canceled'
END
WHERE reservation_id IN (1, 2, 3);

SELECT * FROM "order";