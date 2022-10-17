CREATE OR REPLACE VIEW v4.info AS (
SELECT
    v4.book.name AS bookName,
    v4.genre.name AS bookGenre,
    v4.book.release_date AS release_date,
    v4.book.circulation AS circulation,
    v4.book.price AS price,
    v4.book.pages AS pages,
    v4.author.name AS authorName,
    v4.city.name AS cityName,
    v4.publHouse.name AS publhouse_name
FROM
    v4.book
    LEFT JOIN v4.author ON v4.book.authorID = v4.author.id
    LEFT JOIN v4.city ON v4.author.cityID = v4.city.id
    LEFT JOIN v4.genre ON v4.book.genreID = v4.genre.id
    LEFT JOIN v4.publHouse ON v4.book.publHouseID = v4.publHouse.id
);