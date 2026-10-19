SELECT 
    p.name as name
FROM person p 
JOIN person_order po on p.id = po.person_id
JOIN menu m ON po.menu_id = m.id
WHERE (p.address = 'Moscow' or p.address = 'Samara') AND (m.pizza_name = 'pepperoni pizza' or m.pizza_name = 'mushroom pizza') AND p.gender='male'
ORDER BY name DESC;