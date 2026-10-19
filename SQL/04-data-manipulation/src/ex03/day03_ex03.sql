(SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN person_visits pv on pz.id = pv.pizzeria_id
JOIN person p on pv.person_id = p.id
WHERE p.gender = 'female'
EXCEPT all
SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN person_visits pv on pz.id = pv.pizzeria_id
JOIN person p on pv.person_id = p.id
WHERE p.gender = 'male')
UNION all
(SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN person_visits pv on pz.id = pv.pizzeria_id
JOIN person p on pv.person_id = p.id
WHERE p.gender = 'male'
EXCEPT all
SELECT pz.name as pizzeria_name
FROM pizzeria pz
JOIN person_visits pv on pz.id = pv.pizzeria_id
JOIN person p on pv.person_id = p.id
WHERE p.gender = 'female')
ORDER by pizzeria_name