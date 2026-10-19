SELECT
    p1.name as person_name1,
    p2.name as person_name2,
    p1.address as common_address
from person p1
JOIN person p2 ON p1.address = p2.address AND p1.id > p2.id
ORDER BY person_name1, person_name2, common_address