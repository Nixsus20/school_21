INSERT into person_order (id, person_id, menu_id, order_date)
SELECT
    (SELECT MAX(id) FROM person_order) +p.id,
    p.id,
    (SELECT id FROM menu m WHERE m.pizza_name='greek pizza'),
    '2022-02-25'
from person p;