SELECT 
    po.order_date,
    p.name || ' (age:'||p.age||')' as person_information
FROM person_order po
JOIN person p ON po.person_id = p.id
order by order_date, person_information asc;