DROP SCHEMA IF EXISTS labs CASCADE;
CREATE SCHEMA labs

    CREATE TABLE position(
        id   SERIAL PRIMARY KEY,
        name TEXT UNIQUE
    )

    CREATE TABLE degree(
        id   SERIAL PRIMARY KEY,
        name TEXT UNIQUE
    )
    
    CREATE TABLE courses(
        id   SERIAL PRIMARY KEY,
        name TEXT UNIQUE
    )

    CREATE TABLE teachers(
        id          SERIAL PRIMARY KEY,
        position    INT REFERENCES position (id),
        degree      INT REFERENCES degree (id),
        courses     INT REFERENCES courses (id),
        surname     TEXT,
        room_number INT
    );

INSERT INTO labs.position(name)
VALUES ('Аспирант'),
       ('Профессор'),
       ('Преподаватель'),
       ('Старший преподаватель');

INSERT INTO labs.degree(name)
VALUES ('Кандидат'),
       ('Доктор');

INSERT INTO labs.courses(name)
VALUES ('Веб'),
       ('Клиент-Сервер'),
       ('Компиляторы'),
       ('Экономика'),
       ('БЖД');

INSERT INTO labs.teachers
    (position, degree, courses, surname, room_number)
VALUES (1, 1, 1, 'Попов', 412),
       (2, 2, 2, 'Шаталов', 138),
       (3, 1, 3, 'Игенов', 213),
       (4, 2, 4, 'Герман', 321),
       (1, 1, 5, 'Хейнов', 128);

SELECT * FROM labs.teachers;
