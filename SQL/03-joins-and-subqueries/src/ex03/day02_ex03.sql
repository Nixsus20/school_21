WITH dates as(
    SELECT gs.missing_date::date
    FROM generate_series('2022-01-01'::date, '2022-01-10'::date, '1 day'::interval) as gs(missing_date)
)
SELECT dates.missing_date
FROM dates
left join (
    SELECT visit_date
    FROM person_visits
    WHERE person_id = 1 or person_id = 2
) as pv on dates.missing_date = pv.visit_date
WHERE pv.visit_date is null
order by missing_date asc;