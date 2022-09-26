CREATE VIEW as l1_v4.info AS (
SELECT
    l1_v4.book.name AS bookName
    l1_v4.book.authorID AS bookAuthor
    l1_v4.book.genreID AS bookGenre
    l1_v4.author.cityID AS authorCity
FROM
    l1_v4.book
JOIN
    l1_v4.author
    ON l1_v4.book.authorID = book.id
)