SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN person_visits pv ON pz.id = pv.pizzeria_id
JOIN person p on pv.person_id = p.id
WHERE p.name = 'Andrey'

EXCEPT

SELECT pz.name
FROM pizzeria pz
JOIN menu m on pz.id = m.pizzeria_id
JOIN person_order po ON m.id = po.menu_id
JOIN person p on po.person_id = p.id
WHERE p.name = 'Andrey'

ORDER BY pizzeria_name