SELECT name FROM v_persons_male
UNION
SELECT NAME FROM v_persons_female
ORDER BY name;
