SELECT object_name
FROM (
    SELECT NAME as object_name, 1 as priority
    FROM person
    UNION ALL
    SELECT pizza_name, 2
    FROM menu
) as combined
ORDER BY priority, object_name;