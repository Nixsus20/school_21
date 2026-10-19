CREATE VIEW v_generate_dates AS
SELECT generated_date::DATE
FROM generate_series(
    '2022-01-01'::TIMESTAMP,
    '2022-01-31'::TIMESTAMP,
    '1 day'::INTERVAL
) as generated_date
ORDER BY 1