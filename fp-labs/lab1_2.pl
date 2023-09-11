phone_entry("Андрей", "8-999-999-99-99").
phone_entry("Аркадий", "8-999-999-99-98").
phone_entry("Артем", "8-999-999-99-97").
phone_entry("Артур", "8-999-999-99-96").
phone_entry("Архип", "8-999-999-99-95").
phone_entry("Афанасий", "8-999-999-99-94").
phone_entry("Богдан", "8-999-999-99-93").
phone_entry("Борис", "8-999-999-99-92").
phone_entry("Борислав", "8-999-999-99-91").
phone_entry("Бронислав", "8-999-999-99-90").
phone_entry("Вадим", "8-999-999-99-89").
phone_entry("Валентин", "8-999-999-99-88").
phone_entry("Валерий", "8-999-999-99-87").
phone_entry("Вальтер", "8-999-999-99-86").
phone_entry("Василий", "8-999-999-99-85").
phone_entry("Вениамин", "8-999-999-99-84").
phone_entry("Виктор", "8-999-999-99-83").
phone_entry("Викторий", "8-999-999-99-82").
phone_entry("Вильгельм", "8-999-999-99-81").
phone_entry("Виссарион", "8-999-999-99-80").
phone_entry("Виталий", "8-999-999-99-79").
phone_entry("Владимир", "8-999-999-99-78").
phone_entry("Владислав", "8-999-999-99-77").
phone_entry("Владлен", "8-999-999-99-76").
phone_entry("Влас", "8-999-999-99-75").
phone_entry("Всеволод", "8-999-999-99-74").
phone_entry("Вячеслав", "8-999-999-99-73").
phone_entry("Гавриил", "8-999-999-99-72").
phone_entry("Галактион", "8-999-999-99-71").
phone_entry("Геннадий", "8-999-999-99-70").
phone_entry("Георгий", "8-999-999-99-69").
phone_entry("Герасим", "8-999-999-99-68").
phone_entry("Герман", "8-999-999-99-67").
phone_entry("Глеб", "8-999-999-99-66").
phone_entry("Гордей", "8-999-999-99-65").
phone_entry("Григорий", "8-999-999-99-64").
phone_entry("Давид", "8-999-999-99-63").
phone_entry("Даниил", "8-999-999-99-62").
phone_entry("Данила", "8-999-999-99-61").
phone_entry("Демид", "8-999-999-99-60").
phone_entry("Демьян", "8-999-999-99-59").
phone_entry("Денис", "8-999-999-99-58").
phone_entry("Дмитрий", "8-999-999-99-57").
phone_entry("Добрыня", "8-999-999-99-56").
phone_entry("Донат", "8-999-999-99-55").
phone_entry("Евгений", "8-999-999-99-54").

menu :-
    write("-----------------------------"), nl,
    write("1. Найти номер телефона по имени"), nl,
    write("2. Найти имя по номеру телефона"), nl,
    write("3. Показать весь справочник"), nl,
    write("4. Выход"), nl,
    write("Выбор: "), nl,
    read(Choice),
    menu(Choice).

menu(Choice) :-
    switch(Choice, [
        1: find_number_by_name,
        2: find_name_by_number,
        3: show_directory,
        4: exit
    ]).

find_number_by_name :-
    write("Введите имя: "),
    read(Name),
    find_number_by_name(Name).

find_number_by_name(Name) :-
    phone_entry(Name, PhoneNumber),
    format("Номер телефона для ~w: ~w~n", [Name, PhoneNumber]),
    menu.

find_name_by_number :-
    write("Введите номер телефона: "),
    read(PhoneNumber),
    find_name_by_number(PhoneNumber),
    menu.

find_name_by_number(PhoneNumber) :-
    phone_entry(Name, PhoneNumber),
    format("Имя для номера телефона ~w: ~w~n", [PhoneNumber, Name]).

show_directory :-
    write("Справочник: "), nl,
    show_directory_fail;
    menu.

show_directory_fail :-
    phone_entry(Name, PhoneNumber),
    format("~w: ~w~n", [Name, PhoneNumber]),
    fail. 

exit :-
    write("До свидания!").

switch(X, [Val:Goal|Cases]) :-
    ( X = Val -> call(Goal) ; switch(X, Cases) ).

:- menu.