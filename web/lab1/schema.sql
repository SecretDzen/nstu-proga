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
VALUES ('Aspirant'),
       ('Professor'),
       ('Teacher'),
       ('High Teacher');

INSERT INTO labs.degree(name)
VALUES ('Candidate'),
       ('Doctor');

INSERT INTO labs.courses(name)
VALUES ('Web'),
       ('Client-Server'),
       ('Compilers'),
       ('Economy'),
       ('Life Safety');

INSERT INTO labs.teachers
    (position, degree, courses, surname, room_number)
VALUES (1, 1, 1, 'Popov', 412),
       (2, 2, 2, 'Shatalov', 138),
       (3, 1, 3, 'Igenov', 213),
       (4, 2, 4, 'German', 321),
       (1, 1, 5, 'Kheynov', 128);

SELECT * FROM labs.teachers;
