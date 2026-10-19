SELECT
    p.name as person_name,
    m.pizza_name as pizza_name,
    pz.name as pizzeria_name
FROM person_order po
JOIN person p on po.person_id = p.id
JOIN menu m ON po.menu_id = m.id
JOIN pizzeria pz on m.pizzeria_id = pz.id
ORDER BY person_name, pizza_name, pizzeria_name