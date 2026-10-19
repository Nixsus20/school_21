INSERT INTO person_visits(id,person_id,pizzeria_id,visit_date)
values(
    (SELECT MAX(id)+1 from person_visits),
    (SELECT id from person WHERE name = 'Denis'),
    (SELECT id from pizzeria WHERE name = 'Dominos'),
    '2022-02-24'
);

INSERT INTO person_visits(id,person_id,pizzeria_id,visit_date)
values(
    (SELECT MAX(id)+1 from person_visits),
    (SELECT id from person WHERE name = 'Irina'),
    (SELECT id from pizzeria WHERE name = 'Dominos'),
    '2022-02-24'
);