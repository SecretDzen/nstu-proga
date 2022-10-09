ALTER TABLE
    v4.book
ADD 
bestseller boolean;

UPDATE
    v4.book
SET
    bestseller = false;

UPDATE
    v4.book
SET
    bestseller = true
WHERE 
    circulation > 50000;

CREATE TYPE v4.publ_house_status as enum ('OPEN', 'CLOSED');

ALTER TABLE
    v4.publHouse
ADD
    publStatus v4.publ_house_status;

UPDATE
    v4.publHouse
SET
    publStatus = 'OPEN';

UPDATE
    v4.publHouse
SET
    publStatus = 'CLOSED'
WHERE
    id = 5;
