-- Для каждого карнавального костюма указать сведения о нем

CREATE OR REPLACE VIEW costumes_info AS
SELECT
    p.id,
    p.name,
    pt.name AS costume_type,
    ps.name AS provider,
    m.name  AS producer,
    c.name  AS provider_country,
    c2.name AS producer_country,
    p.price,
    p.age,
    p.produce_date,
    p.provide_date,
    s.sale_date AS sale_date,
    s.quantity AS quantity
FROM costumes AS p
         INNER JOIN costumes_types pt ON pt.id = p.costume_type_id
         INNER JOIN providers ps ON ps.id = p.provider_id
         INNER JOIN producers m ON m.id = p.producer_id
         INNER JOIN countries c2 ON c2.id = m.country_id
         INNER JOIN countries c ON c.id = ps.country_id
         LEFT JOIN sales s ON p.id = s.costume_id;

-- Получить список, отсортированный:
-- по дате выпуска
SELECT * FROM costumes_info ORDER BY produce_date LIMIT 15;
-- по наименованию
SELECT * FROM costumes_info ORDER BY name LIMIT 15;

-- по стоимости,
SELECT * FROM costumes_info ORDER BY price LIMIT 15;

-- по поставщику
SELECT * FROM costumes_info ORDER BY provider LIMIT 15;

-- Найти самый дорогой карнавальный костюм
SELECT * FROM costumes_info WHERE price = (SELECT MAX(price) FROM costumes_info);

-- самый дешёвый карнавальный костюм
SELECT * FROM costumes_info WHERE price = (SELECT MIN(price) FROM costumes_info);

-- среднюю стоимость
SELECT AVG(price) FROM costumes_info;

-- Найти все карнавальные костюмы с ценой свыше 5000 р.
SELECT * FROM costumes_info WHERE price > 5000 LIMIT 15;

-- Найти долю карнавальных костюмов, заданного производителя
WITH total AS (SELECT count(*) AS total
               FROM costumes_info),
     ratio AS (SELECT count(*) AS ratio
                FROM costumes_info
                WHERE producer = 'Dazzle')
SELECT round((ratio.ratio::int * 100.0 / total.total::int)) || '%' as percents
FROM total, ratio;

-- Найти все карнавальные костюмы с заданной датой выпуска
SELECT * FROM costumes_info WHERE provide_date = '2019-07-29' LIMIT 15;

-- Найти долю карнавальных костюмов, чья стоимость находится в заданных пределах (ввод интервала) от общего количества карнавальных костюмов
WITH total AS (SELECT count(*) AS total
               FROM costumes_info),
     ratio AS (SELECT count(*) AS ratio
                FROM costumes_info
                WHERE price between 1000 and 2000)
SELECT round((ratio.ratio::int * 100.0 / total.total::int)) || '%' as percents
FROM total, ratio;

-- Найти долю карнавальных костюмов, поступивших от заданного поставщика (выбор поставщика)
-- от общего числа поставщиков
WITH total AS (SELECT count(*) AS total
               FROM costumes_info),
     ratio AS (SELECT count(*) AS ratio
                FROM costumes_info
                WHERE provider = 'Revel Suit')
SELECT round((ratio.ratio::int * 100.0 / total.total::int)) || '%' as percents
FROM total, ratio;

-- Найти все карнавальне костюмы, поступившие от заданного поставщика (выбор поставщика),
-- чья стоимость больше заданной (ввод стоимости).
SELECT * FROM costumes_info
WHERE provider = 'Revel Suit' AND price > 1000 LIMIT 15;

-- Найти все карнавальные костюмы заданного производителя (выбор)
SELECT * FROM costumes_info WHERE producer = 'Festa' LIMIT 15;

-- Найти долю карнавальных костюмов, проданных за определенный период (ввод периода),
-- от общего времени продаж
WITH total AS (SELECT count(*) AS total
               FROM costumes_info),
     ratio AS (SELECT count(*) AS ratio
                FROM costumes_info
                WHERE sale_date BETWEEN '2021-01-01' AND '2021-06-01')
SELECT round((ratio.ratio::int * 100.0 / total.total::int)) || '%' as percents
FROM total, ratio;

-- Найти все карнавальные костюмы, поступивщие от заданного поставщика,
-- чья стоимость больше, чем средняя стоимость карнавальных костюмов,
-- поступивших из заданной страны (выбор страны)
SELECT * FROM costumes_info 
WHERE provider = 'Revel Suit'
    AND price > (SELECT AVG(price) FROM costumes_info WHERE provider_country = 'Russia') LIMIT 15;

-- Найти долю дешевых карнавальных костюмов (чья стоимость меньше заданной,
-- ввод стоимости), поступивших от заданного поставщика и в целом
WITH total AS (SELECT count(*) AS total
               FROM costumes_info WHERE provider = 'Revel Suit'),
     ratio AS (SELECT count(*) AS ratio
                FROM costumes_info
                WHERE price < 1000 AND provider = 'Revel Suit')
SELECT round((ratio.ratio::int * 100.0 / total.total::int)) || '%' as percents
FROM total, ratio;

-- Найти среднюю стоимость карнавальных костюмов, проданных за определенный
-- промежуток времени (ввод интервала)
SELECT AVG(price) FROM costumes_info WHERE sale_date BETWEEN '2020-01-01' AND '2021-01-01';

-- Найти все карнавальные костюмы, чья стоимость выше, чем средняя стоимость
-- карнавальных костюмов заданного производителя (выбор)
SELECT * FROM costumes_info WHERE price > (
    SELECT AVG(price) FROM costumes_info WHERE producer = 'Festa') LIMIT 15;

-- Найти долю дорогих карнавальных костюмов (чья стоимость больше заданного,
-- ввод стоимости) от общего числа карнавальных костюмов (для каждого возраста (ввод) и в целом)
WITH total AS (SELECT count(*) AS total
               FROM costumes_info WHERE age = 8),
     ratio AS (SELECT count(*) AS ratio
                FROM costumes_info
                WHERE price > 5000 AND age = 8)
SELECT round((ratio.ratio::int * 100.0 / total.total::int)) || '%' as percents
FROM total, ratio;

-- Найти самый дорогой популярный костюм (продано наибольшее количество)
-- для заданного возраста (ввод) и в целом
WITH popular AS (SELECT * FROM costumes_info
    WHERE quantity = (SELECT MAX(quantity) FROM costumes_info))
SELECT * FROM popular
    WHERE price = (SELECT MAX(price) FROM popular)
    AND age = 19;



314 v 6:30