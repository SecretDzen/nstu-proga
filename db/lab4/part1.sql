ALTER TYPE v4.genre_name ADD VALUE 'novel';

BEGIN;

ALTER TABLE v4.genre
    DROP CONSTRAINT genre_name_check;

ALTER TABLE v4.genre
    ADD CONSTRAINT genre_name_check
    CHECK (name IN ('detective', 'science fiction', 'comedy', 'melodrama', 'thriller', 'novel'));

COMMIT;

INSERT INTO
    v4.genre (name)
VALUES
    ('novel');

INSERT INTO
    v4.city (name)
VALUES
    ('Slovakia'),
    ('Rim');

INSERT INTO
    v4.publHouse
    (name, address, cityID)
VALUES
    ('Slova', 'Ratatui 4/2', 11),
    ('Mirt', 'Glavnaya 1', 12);

INSERT INTO
    v4.book
    (name, circulation, price, pages, release_date, authorID, genreID, publHouseID)
VALUES
    ('Work Medicine', 15999, 300, 299, '2021-10-21', 5, 2, 13),
    ('Journal Wokrkout', 33000, 900, 500, '2018-03-11', 3, 6, 11),
    ('Deadly vibe', 23000, 400, 600, '2019-08-11', 3, 6, 12),
    ('Maximaze result', 45000, 180, 800, '2020-11-28', 3, 6, 11),
    ('My understandings', 25000, 250, 250, '2021-10-28', 3, 6, 12),
    ('Pavel Durov real story', 20000, 650, 350, '2022-09-09', 3, 5, 1),
    ('Mi Band II', 20000, 350, 350, '2022-10-09', 3, 1, 1),
    ('Horror at Night Place', 20000, 350, 350, '2022-08-09', 3, 1, 1),
    ('New History', 20000, 200, 350, '2022-09-09', 3, 5, 1);
