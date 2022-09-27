CREATE OR REPLACE VIEW l1_v4.info AS (
SELECT
    l1_v4.book.name AS bookName,
    l1_v4.genre.name AS bookGenre,
    l1_v4.author.name AS authorName,
    l1_v4.city.name AS authorCity
FROM
    l1_v4.book
    LEFT JOIN l1_v4.author ON l1_v4.book.authorID = l1_v4.author.id
    LEFT JOIN l1_v4.city ON l1_v4.author.cityID = l1_v4.city.id
    LEFT JOIN l1_v4.genre ON l1_v4.book.genreID = l1_v4.genre.id
)