SELECT m.id as menu_id
FROM menu m
FULL JOIN person_order po on m.id = po.menu_id
WHERE po.menu_id is NULL
ORDER BY menu_id