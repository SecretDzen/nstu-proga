ALTER TABLE v4.book
ADD pages INT,
ADD price INT;

UPDATE v4.book
SET pages = 256,
    price = 180
WHERE id = 1;

UPDATE v4.book
SET pages = 485,
    price = 615
WHERE id = 2;

UPDATE v4.book
SET pages = 120,
    price = 1500
WHERE id = 3;

UPDATE v4.book
SET pages = 111,
    price = 808
WHERE id = 4;

UPDATE v4.book
SET pages = 324,
    price = 499
WHERE id = 5;

UPDATE v4.book
SET pages = 500,
    price = 3000
WHERE id = 6;

INSERT INTO
    v4.author
    (name, cityID)
VALUES ('Nemirov', 1);

INSERT INTO
    v4.publHouse
    (name, address, cityID)
VALUES ('Siberia', 'Lenina 1', 1);

INSERT INTO
    v4.book
    (name, circulation, pages, price, release_date, authorID, genreID, publHouseID)
VALUES ('Another book', 35000, 350, 1800,  '1999-01-15', 11, 3, 11),
       ('VKontakte Guide', 95000, 220, 660, '2002-10-11', 1, 3, 11),
       ('Bizzare Adventure', 15000, 220, 6600, '2002-10-11', 2, 2, 4),
       ('Bizzare Adventure II', 5000, 120, 660, '2005-10-11', 8, 2, 8);
