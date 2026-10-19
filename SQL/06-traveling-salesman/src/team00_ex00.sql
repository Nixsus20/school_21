CREATE TABLE nodes (
    point1 text NOT NULL,
    point2 text NOT NULL,
    cost   int  NOT NULL
);

INSERT INTO nodes (point1, point2, cost)
VALUES ('a', 'b', 10),
       ('b', 'a', 10),
       ('a', 'c', 15),
       ('c', 'a', 15),
       ('c', 'b', 35),
       ('b', 'c', 35),
       ('a', 'd', 20),
       ('d', 'a', 20),
       ('c', 'd', 30),
       ('d', 'c', 30),
       ('d', 'b', 25),
       ('b', 'd', 25);






WITH RECURSIVE search_path AS (
  SELECT point1 || ',' || point2 AS text_tour, point1, point2, cost, 1 AS depth FROM nodes WHERE point1 = 'a'
  UNION ALL 
  SELECT text_tour || ',' || nodes.point2 AS text_tour, nodes.point1, nodes.point2, nodes.cost + search_path.cost, depth + 1
  FROM search_path
  JOIN nodes ON search_path.point2 = nodes.point1 WHERE search_path.text_tour NOT LIKE '%'||nodes.point2||'%'
), nodesp2 AS (SELECT * FROM nodes WHERE point2 = 'a'
), gotovo AS (SELECT np2.cost + search_path.cost AS total_cost, '{' || search_path.text_tour || ',' || 'a' || '}' AS tour FROM search_path
JOIN nodesp2 np2 ON np2.point1 = search_path.point2
WHERE depth = 3
ORDER BY 1, 2)
SELECT * FROM gotovo WHERE total_cost = (SELECT MIN(total_cost) FROM gotovo)
ORDER BY total_cost, tour;