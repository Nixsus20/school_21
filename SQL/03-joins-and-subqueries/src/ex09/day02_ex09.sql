SELECT
    p.name
FROM person p 
JOIN person_order po on p.id = po.person_id
JOIN menu m ON po.menu_id = m.id
WHERE m.pizza_name = 'pepperoni pizza' AND p.gender='female'

intersect

SELECT
    p.name
FROM person p 
JOIN person_order po on p.id = po.person_id
JOIN menu m ON po.menu_id = m.id
WHERE m.pizza_name = 'cheese pizza' AND p.gender='female'
ORDER BY name;