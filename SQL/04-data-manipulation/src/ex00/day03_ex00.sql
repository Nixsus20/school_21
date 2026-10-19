SELECT
    m.pizza_name,
    m.price,
    pz.name as pizzeria_name,
    pv.visit_date
FROM person p
JOIN person_visits pv ON p.id = pv.person_id
JOIN pizzeria pz on pv.pizzeria_id = pz.id
JOIN menu m ON pz.id = m.pizzeria_id
WHERE p.name='Kate' AND m.price BETWEEN 800 and 1000
ORDER BY m.pizza_name, m.price, pizzeria_name