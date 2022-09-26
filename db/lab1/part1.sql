DROP SCHEMA IF EXISTS l1_v4 CASCADE;
CREATE SCHEMA l1_v4;

CREATE TABLE l1_v4.city (
    id   SERIAL,
    name VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE l1_v4.genre (
    id   SERIAL,
    name VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE l1_v4.publHouse (
    id      SERIAL,
    name    VARCHAR NOT NULL,
    address VARCHAR NOT NULL,
    cityID  INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (cityID) REFERENCES l1_v4.city(id)
);

CREATE TABLE l1_v4.author (
    id     SERIAL,
    name   VARCHAR NOT NULL,
    cityID INT NOT NULL, 

    PRIMARY KEY (id),
    FOREIGN KEY (cityID) REFERENCES l1_v4.city(id)
);

CREATE TABLE l1_v4.book (
    id          SERIAL,
    circulation INT NOT NULL,
    authorID    INT NOT NULL,
    genreID     INT NOT NULL,
    publHouseID INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (authorID)    REFERENCES l1_v4.author(id),
    FOREIGN KEY (genreID)     REFERENCES l1_v4.genre(id),
    FOREIGN KEY (publHouseID) REFERENCES l1_v4.publHouse(id)
);

SET timezone = 'Asia/Novosibirsk';