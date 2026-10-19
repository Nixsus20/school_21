WITH RECURSIVE search_path AS (
  SELECT point1 || ',' || point2 AS text_tour, point1, point2, cost, 1 AS depth FROM nodes WHERE point1 = 'a'
  UNION ALL 
  SELECT text_tour || ',' || nodes.point2 AS text_tour, nodes.point1, nodes.point2, nodes.cost + search_path.cost, depth + 1
  FROM search_path
  JOIN nodes ON search_path.point2 = nodes.point1 WHERE search_path.text_tour NOT LIKE '%' || nodes.point2 || '%'
), nodesp2 AS (SELECT * FROM nodes WHERE point2 = 'a')
SELECT np2.cost + search_path.cost AS total_cost, '{' || search_path.text_tour || ',' || 'a' || '}' AS tour FROM search_path
JOIN nodesp2 np2 ON np2.point1 = search_path.point2
WHERE depth = 3
ORDER BY total_cost, tour;