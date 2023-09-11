DO
$do$
BEGIN
    IF EXISTS (SELECT FROM pg_user
        WHERE  usename = 'desolaye'
        ) THEN
        RAISE NOTICE 'User already exists';
    ELSE
        CREATE ROLE desolaye WITH CREATEDB NOCREATEROLE LOGIN PASSWORD '123456';
    END IF;
END
$do$;

ALTER DATABASE labs_db OWNER TO desolaye;
