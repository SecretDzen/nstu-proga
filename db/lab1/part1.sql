DROP SCHEMA IF EXISTS v4 CASCADE;
CREATE SCHEMA v4;

CREATE TABLE v4.city (
    id   SERIAL,
    name VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE v4.genre (
    id   SERIAL,
    name VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE v4.publHouse (
    id      SERIAL,
    name    VARCHAR NOT NULL,
    address VARCHAR NOT NULL,
    cityID  INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (cityID) REFERENCES v4.city(id)
);

CREATE TABLE v4.author (
    id     SERIAL,
    name   VARCHAR NOT NULL,
    cityID INT NOT NULL, 

    PRIMARY KEY (id),
    FOREIGN KEY (cityID) REFERENCES v4.city(id)
);

CREATE TABLE v4.book (
    id          SERIAL,
    name        VARCHAR,
    circulation INT NOT NULL,
    authorID    INT NOT NULL,
    genreID     INT NOT NULL,
    publHouseID INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (authorID)    REFERENCES v4.author(id),
    FOREIGN KEY (genreID)     REFERENCES v4.genre(id),
    FOREIGN KEY (publHouseID) REFERENCES v4.publHouse(id)
);

SET timezone = 'Asia/Novosibirsk';