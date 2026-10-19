(SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN menu m on pz.id = m.pizzeria_id
JOIN person_order po on m.id = po.menu_id
JOIN person p on po.person_id = p.id
WHERE p.gender = 'male'
EXCEPT
SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN menu m on pz.id = m.pizzeria_id
JOIN person_order po on m.id = po.menu_id
JOIN person p on po.person_id = p.id
WHERE p.gender = 'female')
UNION
(SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN menu m on pz.id = m.pizzeria_id
JOIN person_order po on m.id = po.menu_id
JOIN person p on po.person_id = p.id
WHERE p.gender = 'female'
EXCEPT
SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN menu m on pz.id = m.pizzeria_id
JOIN person_order po on m.id = po.menu_id
JOIN person p on po.person_id = p.id
WHERE p.gender = 'male')
ORDER BY pizzeria_name