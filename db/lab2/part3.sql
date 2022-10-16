INSERT INTO
    v4.city
    (name)
VALUES
    ('Moscow'),
    ('Saint-Petersburg'),
    ('Novosibirsk'),
    ('Krasnodar'),
    ('Kazan'),
    ('Ufa'),
    ('Samara'),
    ('Omsk'),
    ('Saratov'),
    ('Perm');

INSERT INTO
    v4.genre
    (name)
VALUES
    ('detective'),
    ('science fiction'),
    ('comedy'),
    ('melodrama'),
    ('thriller');

INSERT INTO
    v4.publHouse
    (name, address, cityID)
VALUES
    ('Romanco', 'Mira 14/2', 1),
    ('Sciencia', 'Lenina 9k2', 2),
    ('Myst & Co.', 'Sadovaya 2', 3),
    ('Fanta Limited Co.', 'Lynnaya 126', 4),
    ('Horrorita', 'Pushkina 15', 5),
    ('All Ficti', 'Glavnaya 166', 6),
    ('History Supremacy', 'Pobochnaya 1', 7),
    ('Thrill&Chill', 'Odina 22k3', 8),
    ('BioPeople', 'Petrova 11', 9),
    ('Books&Cooks', 'Dumskaya 9', 10);

INSERT INTO
    v4.author
    (name, cityID)
VALUES
    ('Mokan', 1),
    ('Baranova', 2),
    ('Ivanov', 3),
    ('Lebedev', 4),
    ('Smirnov', 5),
    ('Kolokolov', 6),
    ('Alekseev', 7),
    ('Pavlov', 8),
    ('Kozlov', 9),
    ('Isaev', 10);

INSERT INTO
    v4.book
    (name, circulation, price, release_date, authorID, genreID, publHouseID)
VALUES
    ('1985', 65000, 250, '2001-10-28', 1, 1, 1),
    ('Tarrok and his fish', 23000, 180, '2020-05-11', 3, 3, 3),
    ('Kasiposha adventure', 55000, 660, '2021-01-20', 2, 2, 2),
    ('Magistrate 2020', 11000, 195, '1999-05-18', 4, 4, 4),
    ('In Search Of Lost Keys', 200000, 666, '1985-02-24', 5, 5, 5),
    ('Moby Don key-cat', 51000, 895, '2001-11-01', 6, 1, 6),
    ('War and War', 67000, 999, '2005-09-30', 7, 2, 7),
    ('IKEA Tutorial', 42500, 1200, '2009-04-11' ,8, 3, 8),
    ('My cat - Vengeance', 25000, 1500, '2022-03-08' ,9, 4, 9),
    ('Catch-44', 69000, 1800, '2019-05-28', 10, 5, 10);

-- Incorrect inserts
INSERT INTO
    v4.book
    (name, circulation, price ,release_date, authorID, genreID, publHouseID)
VALUES
    ('Final Fantasy', 45000, 999, '2023-10-28', 1, 1, 1);

INSERT INTO
    v4.book
    (name, circulation, price, release_date, authorID, genreID, publHouseID)
VALUES
    ('Find the Mise', 20, 999, '2019-05-28', 10, 5, 10);

INSERT INTO
    v4.book
    (name, circulation, price, release_date, authorID, genreID, publHouseID)
VALUES
    ('Find the Mise', 1920, 5, '2019-05-28', 10, 5, 10);

INSERT INTO
    v4.genre
    (name)
VALUES
    ('Not a genre');