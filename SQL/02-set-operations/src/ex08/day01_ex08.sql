SELECT 
    po.order_date,
    p.name || ' (age:'||p.age||')' as person_information
FROM (SELECT order_date, person_id as id FROM person_order) as po
Natural JOIN person p
order by order_date, person_information asc;