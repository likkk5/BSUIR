-- Копируем значения из одной таблицы в другую
INSERT INTO guest (user_id) 
SELECT id FROM "user" 
WHERE role_id = (SELECT id FROM roles WHERE role_name = 'Guest')
ON CONFLICT (user_id) DO NOTHING;

ALTER TABLE guest ADD CONSTRAINT unique_user_id UNIQUE (user_id);
-- Добавляем в таблицу guest только тех пользователей с ролью 'Guest', у которых ещё нет записи в guest.