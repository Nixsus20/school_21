--дмитрий заказ в best pizza 01.08
INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
values(
    (SELECT MAX(id)+1 FROM person_visits),
    (SELECT id FROM person WHERE name='Dmitriy'),
    (SELECT id FROM pizzeria WHERE name='Best Pizza'),
    '2022-01-08'
);

refresh MATERIALIZED VIEW mv_dmitriy_visits_and_eats;