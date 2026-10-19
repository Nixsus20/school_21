-- Independent sample data for smoke-testing the published SQL exercises.
-- This is NOT the School 21 dataset. Do not compare query output with School 21 answers.
-- Every SQL series is executed in its own throwaway PostgreSQL database.

CREATE TABLE person (
  id bigint PRIMARY KEY,
  name text NOT NULL,
  age integer NOT NULL,
  gender text NOT NULL CHECK (gender IN ('male', 'female')),
  address text NOT NULL
);

CREATE TABLE pizzeria (
  id bigint PRIMARY KEY,
  name text NOT NULL,
  rating numeric NOT NULL CHECK (rating BETWEEN 0 AND 5)
);

CREATE TABLE menu (
  id bigint PRIMARY KEY,
  pizzeria_id bigint NOT NULL REFERENCES pizzeria(id),
  pizza_name text NOT NULL,
  price numeric NOT NULL
);

CREATE TABLE person_visits (
  id bigint PRIMARY KEY,
  person_id bigint NOT NULL REFERENCES person(id),
  pizzeria_id bigint NOT NULL REFERENCES pizzeria(id),
  visit_date date NOT NULL,
  UNIQUE (person_id, pizzeria_id, visit_date)
);

CREATE TABLE person_order (
  id bigint PRIMARY KEY,
  person_id bigint NOT NULL REFERENCES person(id),
  menu_id bigint NOT NULL REFERENCES menu(id),
  order_date date NOT NULL
);

INSERT INTO person(id, name, age, gender, address) VALUES
  (1,'Anna',25,'female','Kazan'),
  (2,'Andrey',28,'male','Moscow'),
  (3,'Kate',30,'female','Kazan'),
  (4,'Denis',20,'male','Kazan'),
  (5,'Mila',32,'female','Samara'),
  (6,'Irina',27,'female','Moscow'),
  (7,'Peter',35,'male','Samara'),
  (8,'Elena',24,'female','Moscow'),
  (9,'Dmitriy',29,'male','Samara');

INSERT INTO pizzeria(id, name, rating) VALUES
  (1,'Brick Oven',4.2),
  (2,'Dominos',4.5),
  (3,'PizzaLab',3.7),
  (4,'North Slice',4.9),
  (5,'City Pizza',3.1),
  (6,'Riverside Pizza',4.0);

INSERT INTO menu(id, pizzeria_id, pizza_name, price) VALUES
  (1,1,'cheese pizza',690),
  (2,1,'pepperoni pizza',930),
  (3,1,'mushroom pizza',790),
  (4,1,'sausage pizza',810),
  (5,2,'cheese pizza',790),
  (6,2,'pepperoni pizza',880),
  (7,2,'mushroom pizza',980),
  (8,2,'margherita pizza',770),
  (9,3,'cheese pizza',700),
  (10,3,'mushroom pizza',810),
  (11,3,'sausage pizza',910),
  (12,4,'cheese pizza',730),
  (13,4,'mushroom pizza',930),
  (14,4,'pepperoni pizza',990),
  (15,4,'veggie pizza',890),
  (16,5,'cheese pizza',660),
  (17,5,'pepperoni pizza',790),
  (18,6,'mushroom pizza',880);

INSERT INTO person_visits(id, person_id, pizzeria_id, visit_date) VALUES
  (1,1,1,'2022-01-01'),
  (2,2,2,'2022-01-01'),
  (3,2,1,'2022-01-02'),
  (4,3,4,'2022-01-03'),
  (5,3,5,'2022-01-04'),
  (6,4,1,'2022-01-07'),
  (7,4,2,'2022-01-08'),
  (8,5,2,'2022-01-08'),
  (9,5,4,'2022-01-09'),
  (10,6,2,'2022-01-09'),
  (11,6,4,'2022-01-01'),
  (12,7,1,'2022-01-03'),
  (13,7,2,'2022-01-05'),
  (14,8,1,'2022-01-05'),
  (15,8,2,'2022-01-06'),
  (16,8,4,'2022-01-07'),
  (17,9,1,'2022-01-08'),
  (18,9,5,'2022-01-09'),
  (19,9,6,'2022-01-10');

INSERT INTO person_order(id, person_id, menu_id, order_date) VALUES
  (1,1,1,'2022-01-01'),
  (2,1,2,'2022-01-01'),
  (3,2,5,'2022-01-01'),
  (4,2,6,'2022-01-01'),
  (5,3,16,'2022-01-04'),
  (6,4,13,'2022-01-07'),
  (7,4,14,'2022-01-07'),
  (8,4,18,'2022-01-07'),
  (9,4,6,'2022-01-08'),
  (10,4,7,'2022-01-08'),
  (11,5,6,'2022-01-09'),
  (12,5,7,'2022-01-09'),
  (13,6,13,'2022-01-01'),
  (14,7,3,'2022-01-03'),
  (15,7,9,'2022-01-05'),
  (16,7,4,'2022-01-05'),
  (17,8,8,'2022-01-06'),
  (18,8,14,'2022-01-07'),
  (19,9,18,'2022-01-09'),
  (20,9,6,'2022-01-10');
