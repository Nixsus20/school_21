SELECT id as object_id, name as object_name
FROM person
UNION
SELECT id as object_id, pizza_name as object_name
FROM menu
ORDER BY object_id, object_name;