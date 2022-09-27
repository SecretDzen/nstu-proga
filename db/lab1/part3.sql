ALTER TABLE
    l1_v4.book
ADD 
bestseller boolean;

UPDATE
    l1_v4.book
SET
    bestseller = false;

UPDATE
    l1_v4.book
SET
    bestseller = true
WHERE 
    circulation > 50000;

CREATE TYPE l1_v4.publ_house_status as enum ('OPEN', 'CLOSED');

ALTER TABLE
    l1_v4.publHouse
ADD
    publStatus l1_v4.publ_house_status;

UPDATE
    l1_v4.publHouse
SET
    publStatus = 'OPEN';

UPDATE
    l1_v4.publHouse
SET
    publStatus = 'CLOSED'
WHERE
    id = 5;
