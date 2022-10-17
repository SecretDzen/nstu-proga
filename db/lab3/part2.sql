CREATE TABLE v4.binding (
    id       INT,
    material VARCHAR[],
    color    VARCHAR[][],

    PRIMARY KEY (id)
);

INSERT INTO v4.binding
VALUES
    (1, '{"wood", "metal", "paper"}', '{{"black", "white", "yellow"}, {"pink", "blue", "mangheta"}, {"brown", "green", "red"}}');

INSERT INTO v4.binding
VALUES
    (3, '{"stone", "leather"}');

INSERT INTO v4.binding
VALUES
    (4, '{}', '{{"gray", "dim"}}');

INSERT INTO v4.binding
VALUES
    (5, '{"plastic", "ice", "cotton"}', '{{"red", "mango", "teal"}, {"indigo", "raspberry", "aqua"}, {"beige", "gold", "olive"}}');


SELECT material[1] FROM v4.binding;
SELECT material[1] FROM v4.binding WHERE material[1] IS NOT NULL;

SELECT material[2] as material, color[1][1] as first_col, color[1][2] as second_col FROM v4.binding;
SELECT color[1:3] FROM v4.binding;

SELECT array_dims(material) FROM v4.binding;
SELECT array_dims(color) FROM v4.binding;
