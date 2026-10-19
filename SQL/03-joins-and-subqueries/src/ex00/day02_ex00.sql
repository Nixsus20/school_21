SELECT
    p.name,
    p.rating
FROM pizzeria p
LEFT JOIN person_visits pv on p.id = pv.pizzeria_id
WHERE pv.id is NULL