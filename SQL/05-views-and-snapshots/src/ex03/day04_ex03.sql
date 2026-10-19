SELECT generated_date as mising_date
FROM v_generate_dates

EXCEPT

SELECT visit_date
FROM person_visits 

ORDER BY 1