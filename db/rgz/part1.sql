-- schema creation
DROP SCHEMA IF EXISTS public CASCADE;
CREATE SCHEMA IF NOT EXISTS public;

-- tables creation
CREATE TABLE IF NOT EXISTS countries(
    id SERIAL,
    name VARCHAR UNIQUE NOT NULL,
    code CHAR(2) UNIQUE NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS producers(
    id         SERIAL,
    name       VARCHAR UNIQUE NOT NULL,
    country_id INT,

    PRIMARY KEY (id),
    FOREIGN KEY (country_id) REFERENCES countries(id)
);

CREATE TABLE IF NOT EXISTS providers(
    id         SERIAL,
    name       VARCHAR UNIQUE NOT NULL,
    country_id INT,

    PRIMARY KEY (id),
    FOREIGN KEY (country_id) REFERENCES countries(id)
);

CREATE TABLE IF NOT EXISTS costumes_types(
    id   SERIAL,
    name VARCHAR UNIQUE NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS costumes(
    id              SERIAL,
    name            VARCHAR NOT NULL,
    age             INT     NOT NULL,
    price           INT     NOT NULL,
    produce_date    DATE    NOT NULL,
    provide_date    DATE    NOT NULL,
    provider_id     INT     NOT NULL,
    producer_id     INT     NOT NULL,
    costume_type_id INT     NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (provider_id) REFERENCES providers(id),
    FOREIGN KEY (producer_id) REFERENCES producers(id),
    FOREIGN KEY (costume_type_id) REFERENCES costumes_types(id)
);

CREATE TABLE IF NOT EXISTS clients(
    id   SERIAL,
    name VARCHAR NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS sales(
    id          SERIAL,
    sale_date   DATE    NOT NULL,
    quantity    INT     NOT NULL,
    total_price INT     NOT NULL,
    costume_id  INT,
    client_id   INT,

    PRIMARY KEY (id),
    FOREIGN KEY (costume_id) REFERENCES costumes(id),
    FOREIGN KEY (client_id) REFERENCES clients(id)
);
