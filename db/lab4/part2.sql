-- Найти все повести и романы, в которых от 250 до 500 страниц, и с ценой больше,
-- чем средняя цена книг издательствa Fanta Limited Co. (4)

SELECT
    v4.book.name AS book_name,
    v4.book.pages AS book_pages,
    v4.book.price AS book_price,
    v4.genre.name AS genre_name,
    v4.publHouse.name AS publhouse_name
FROM v4.book
    LEFT JOIN v4.publHouse ON v4.book.publHouseID = v4.publHouse.id
    LEFT JOIN v4.genre ON v4.book.genreID = v4.genre.id
WHERE v4.genre.name = 'novel'
    AND v4.book.pages > 249
    AND v4.book.pages < 501
    AND v4.book.price > (
        SELECT(AVG(v4.book.price))
        FROM v4.book
            LEFT JOIN v4.publHouse ON v4.book.publHouseID = v4.publHouse.id
            WHERE v4.publHouse.name = 'Fanta Limited Co.');

-- Найти всю литературу автора Иванова, выпущенную в Москве и Новосибирске, и с ценой выше, чем средняя
-- цена произведений жанра «детектив», выпущенных за последние полгода, автором Ивановым.

SELECT
    v4.book.name AS book_name,
    v4.city.name AS city_name,
    v4.book.release_date AS release_date,
    v4.author.name AS author_name,
    v4.book.price AS book_price,
    v4.genre.name AS genre_name
FROM v4.book
    LEFT JOIN v4.publHouse ON v4.book.publHouseID = v4.publHouse.id
    LEFT JOIN v4.genre ON v4.book.genreID = v4.genre.id
    LEFT JOIN v4.author ON v4.book.authorID = v4.author.id
    LEFT JOIN v4.city ON v4.author.cityID = v4.city.id
WHERE v4.author.name = 'Ivanov'
    AND (v4.city.name = 'Moscow' OR v4.city.name = 'Novosibirsk')
    AND v4.book.price > (
        SELECT(AVG(v4.book.price))
        FROM v4.book
            LEFT JOIN v4.genre ON v4.book.genreID = v4.genre.id
            WHERE (v4.book.release_date > current_date::date - interval '6 months')
            AND (v4.genre.name = 'detective'));

-- Найти все поэтические произведения Fanta Limited Co.
-- и с ценой больше, чем средняя цена книг, выпущенных в Чехии и Словакии

SELECT
    v4.book.name AS book_name,
    v4.book.price AS book_price,
    v4.publHouse.name AS publ_house,
    v4.city.name AS city_name
FROM v4.book
    LEFT JOIN v4.author ON v4.book.authorID = v4.author.id
    LEFT JOIN v4.publHouse ON v4.book.publHouseID = v4.publHouse.id
    LEFT JOIN v4.city ON v4.author.cityID = v4.city.id
WHERE
    v4.publHouse.name = 'Fanta Limited Co.'
    AND v4.book.price > (
        SELECT (AVG(v4.book.price))
        FROM v4.book
            LEFT JOIN v4.publHouse ON v4.book.publHouseID = v4.publHouse.id
            LEFT JOIN v4.city ON v4.publHouse.cityID = v4.city.id
            WHERE
                (v4.city.name = 'Rim' OR v4.city.name = 'Slovakia')
    );
