-- Role drops
DROP ROLE IF EXISTS operator;
DROP ROLE IF EXISTS db_user;
DROP ROLE IF EXISTS admin;

-- Create base roles
CREATE ROLE operator WITH LOGIN PASSWORD 'qwerty';
CREATE ROLE db_user WITH LOGIN PASSWORD 'qwerty';
CREATE ROLE admin WITH LOGIN PASSWORD 'qwerty';

-- Give access to schema public
GRANT USAGE ON SCHEMA public TO operator;
GRANT USAGE ON SCHEMA public TO db_user;
GRANT USAGE ON SCHEMA public TO admin;

GRANT ALL ON SCHEMA public TO admin;
GRANT ALL ON SCHEMA public TO operator;
GRANT ALL ON SCHEMA public TO db_user;

GRANT SELECT, USAGE ON all sequences IN SCHEMA public TO operator;
grant SELECT, USAGE ON all sequences IN SCHEMA public TO db_user;
GRANT all privileges ON all sequences in schema public TO admin;

-- Give access on tables dictionaries for operator, for db_user on others, for admin - give access on all
GRANT INSERT, SELECT, UPDATE, DELETE ON countries, producers, costumes_types to operator;
GRANT INSERT, SELECT, UPDATE, DELETE ON costumes, providers, clients, sales to db_user;
GRANT all privileges ON all tables IN SCHEMA public TO admin;
