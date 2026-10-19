SELECT id, NAME,
    case
        when age >= 10 and age <= 20 THEN 'interval #1'
        when age > 20 and age < 24 THEN 'interval #2'
        else 'interval #3'
    end as interval_info
from person
ORDER BY interval_info asc;