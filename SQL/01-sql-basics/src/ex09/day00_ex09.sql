SELECT 
    (SELECT name from person WHERE id = pv.person_id) as person_name,
    (SELECT name from pizzeria WHERE id = pv.pizzeria_id) as pizzaria_name
from (
    SELECT person_id, pizzeria_id
    from person_visits
    WHERE visit_date between '2022-01-07' and '2022-01-09'
) as pv
order by person_name asc, pizzeria_id desc;