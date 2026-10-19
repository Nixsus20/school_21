INSERT INTO menu (id, pizzeria_id,pizza_name,price)
values (
    (SELECT MAX(id) + 1 from menu),
    (SELECT id from pizzeria WHERE name = 'Dominos'),
    'sicilian pizza',
    900
);
