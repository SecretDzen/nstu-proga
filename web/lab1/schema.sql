DROP SCHEMA IF EXISTS labs CASCADE;
CREATE SCHEMA labs

    CREATE TABLE position
    (
        id   serial PRIMARY KEY,
        name text UNIQUE
    )

    CREATE TABLE degree
    (
        id   serial PRIMARY KEY,
        name text UNIQUE
    )

    CREATE TABLE courses
    (
        id   serial PRIMARY KEY,
        name text UNIQUE
    )

    CREATE TABLE teachers
    (
        id          serial PRIMARY KEY,
        position    int REFERENCES position (id),
        degree      int REFERENCES degree (id),
        courses     int REFERENCES courses (id),
        surname     text,
        room_number int
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

SELECT *
FROM labs.teachers;

CREATE TABLE users
(
    id           serial PRIMARY KEY,
    login        text NOT NULL,
    password     text NOT NULL,
    access_level int  NOT NULL DEFAULT 0
);

INSERT INTO users (login, password, access_level)
VALUES ('admin', 'qwertyqwerty', 2),
       ('operator', '123123', 1);