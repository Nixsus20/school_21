SELECT NAME
FROM pizzeria
WHERE id not in (SELECT pizzeria_id from person_visits);

SELECT NAME
FROM pizzeria
WHERE not EXISTS(
    SELECT 1
    FROM person_visits
    WHERE person_visits.pizzeria_id = pizzeria.id);