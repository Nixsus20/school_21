SELECT 
    pizza_name,
    pz.name as pizzeria_name
FROM menu m
JOIN pizzeria pz on m.pizzeria_id = pz.id
JOIN person_order po ON m.id = po.menu_id
JOIN person p on po.person_id = p.id
WHERE p.name = 'Denis' or p.name = 'Anna'
ORDER by pizza_name, pizzeria_name