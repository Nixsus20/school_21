SELECT 
    m.pizza_name,
    m.price,
    pz.name as pizzeria_name
FROM menu m
FULL JOIN person_order po on m.id = po.menu_id
JOIN pizzeria pz on m.pizzeria_id = pz.id
WHERE po.menu_id is NULL
ORDER BY pizza_name, price