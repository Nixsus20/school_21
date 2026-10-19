SELECT 
    action_date,
    (SELECT name FROM person WHERE id = combined.person_id) as person_name
FROM (
    SELECT order_date as action_date, person_id FROM person_order
    INTERSECT all
    SELECT visit_date, person_id FROM person_visits
) as combined
ORDER BY action_date ASC, person_name DESC