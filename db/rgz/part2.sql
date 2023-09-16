-- fill tables with entities

INSERT INTO
    countries(name, code)
VALUES
    ('China', 'ch'),
    ('USA', 'us'),
    ('Germany', 'de'),
    ('Russia', 'ru'),
    ('France', 'fr'),
    ('Italy', 'it'),
    ('UK', 'uk'),
    ('Japan', 'jp'),
    ('Spain', 'es'),
    ('Canada', 'ca');

INSERT INTO producers(name, country_id)
VALUES ('Reno', 1),
       ('NYCarnaval', 2),
       ('Haysde', 3),
       ('Festa', 4),
       ('MardiBoo', 5),
       ('TaTa', 6),
       ('Costumex', 7),
       ('DressedUp', 8),
       ('Mascotoin', 9),
       ('Dazzle', 10);

INSERT INTO
    providers(name, country_id)
VALUES
    ('Carni Clothers', 1),
    ('Revel Suit', 2),
    ('Play Tiara', 3),
    ('Carco', 4),
    ('Jubi Wear', 5),
    ('Crazoot', 6),
    ('Outfest', 7),
    ('Merri Colors', 8),
    ('Festodo', 9),
    ('Funtasia', 10);

INSERT INTO
    costumes_types(name)
VALUES
    ('Венецианский'),
    ('Сезонный'),
    ('Праздничный'),
    ('Традиционный'),
    ('Открытый'),
    ('Сборный'),
    ('Торжественный'),
    ('Сказочный'),
    ('Театральный'),
    ('Простой');

INSERT INTO
    clients(name)
VALUES
    ('Анатолий Бахарев'),
    ('Антон Городецкий'),
    ('Светлана Раскольникова'),
    ('Лев Толстой'),
    ('Александр Македонский'),
    ('Василий Леонтьев'),
    ('Ирина Захарова'),
    ('Андрей Чернышёв'),
    ('Дмитрий Галустян'),
    ('Ольга Прокофьева');
