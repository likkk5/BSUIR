-- получить информацию о том, как будет выполняться запрос
EXPLAIN
SELECT *
FROM guest
INNER JOIN "user" ON "user".id = guest.user_id;

EXPLAIN
SELECT *
FROM "user"
WHERE id > 5;
