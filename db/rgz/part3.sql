-- fill costumes and sales with entities

-- random varchar from given length
CREATE OR REPLACE FUNCTION rand_str(len DOUBLE PRECISION) RETURNS VARCHAR AS
$$
DECLARE
    chars VARCHAR[] := '{0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}';
    result VARCHAR := '';
    i INTEGER := 0;
BEGIN
  FOR i IN 1..len LOOP
    result := result || chars[1+random()*(array_length(chars, 1)-1)];
  END LOOP;
  RETURN result;
END;
$$ LANGUAGE 'plpgsql';

-- func to randomly create costumes
CREATE OR REPLACE FUNCTION fill_costumes(n integer)
    RETURNS void AS
$DO$
DECLARE
    _type         INT;
    _name         VARCHAR;
    _producer     INT;
    _provider     INT;
    _price        INT;
    _age          INT;
    _produce_date DATE;
    _provide_date DATE;

BEGIN
    for i IN 1..n
        LOOP
            _type = (SELECT id FROM costumes_types ORDER BY random() LIMIT 1);
            _producer = (SELECT id FROM producers ORDER BY random() LIMIT 1);
            _provider = (SELECT id FROM providers ORDER BY random() LIMIT 1);
            _price = (SELECT random() * 10000)::int;
            _age = ((SELECT random() * 17)::int + 4);
            _produce_date = '2020-01-01'::date + (SELECT random() * 365)::int;
            _provide_date = _produce_date + (SELECT random() * 365)::int;
            _name = (SELECT * FROM rand_str((random() * 6 + 6)::int));

            INSERT INTO costumes (costume_type_id, producer_id, provider_id, price, name, age, produce_date, provide_date)
            VALUES (_type, _producer, _provider, _price, _name, _age, _produce_date, _provide_date);
        end LOOP;
END;
$DO$ language plpgsql;

-- func to randomly create sales
CREATE OR REPLACE FUNCTION fill_sales(n integer)
    RETURNS void AS
$DO$
DECLARE
    t            INT;
    _costume_id  INT;
    _client_id   INT;
    _sale_date   DATE;
    _quantity    INT;
    _total_price INT;
BEGIN
    for i in 1..n
        LOOP
            _costume_id = (SELECT id FROM costumes ORDER BY random() limit 1);
            _sale_date =  (SELECT provide_date FROM costumes WHERE id = _costume_id)::date + (SELECT random() * 365)::int;
            _client_id = (SELECT id FROM clients ORDER BY random() limit 1);
            _quantity = (SELECT random() * 10)::int;
            _total_price = (SELECT price FROM costumes WHERE id = _costume_id) * _quantity;
            INSERT INTO sales (sale_date, quantity, total_price, costume_id, client_id)
            VALUES (_sale_date, _quantity, _total_price, _costume_id, _client_id);
        END LOOP;
END;
$DO$ language plpgsql;

-- usage of those funcs
select fill_costumes(1000);
select fill_sales(250);
