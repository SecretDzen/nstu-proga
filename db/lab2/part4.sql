CREATE OR REPLACE VIEW v4.info AS (
SELECT
    v4.book.name AS bookName,
    v4.genre.name AS bookGenre,
    v4.author.name AS authorName,
    v4.city.name AS authorCity
FROM
    v4.book
    LEFT JOIN v4.author ON v4.book.authorID = v4.author.id
    LEFT JOIN v4.city ON v4.author.cityID = v4.city.id
    LEFT JOIN v4.genre ON v4.book.genreID = v4.genre.id
)