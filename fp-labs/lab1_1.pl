man("Александр").
man("Иван").
man("Дмитрий").
man("Андрей").
man("Артем").
man("Михаил").
man("Сергей").
man("Никита").
man("Максим").
man("Том Браун").

woman("Екатерина").
woman("Анастасия").
woman("Харуми").
woman("Ольга").
woman("Татьяна").
woman("Анна").
woman("Мария").
woman("Светлана").
woman("Елена").
woman("Наталья").
woman("Ирина").

married("Дмитрий", "Екатерина").
married("Максим", "Харуми").
married("Никита", "Светлана").
married("Сергей", "Ирина").
married("Артем", "Наталья").
married("Том Браун", "Анастасия").

parent("Никита", "Анна").
parent("Светлана", "Анна").
parent("Никита", "Сергей").
parent("Светлана", "Сергей").
parent("Дмитрий", "Ирина").
parent("Екатерина", "Ирина").
parent("Дмитрий", "Иван").
parent("Екатерина", "Иван").
parent("Дмитрий", "Максим").
parent("Екатерина", "Максим").
parent("Том Браун", "Харуми").
parent("Анастасия", "Харуми").
parent("Сергей", "Андрей").
parent("Ирина", "Андрей").
parent("Максим", "Михаил").
parent("Харуми", "Михаил").
parent("Максим", "Ольга").
parent("Харуми", "Ольга").
parent("Максим", "Татьяна").
parent("Харуми", "Татьяна").
parent("Артем", "Елена").
parent("Наталья", "Елена").
parent("Артем", "Александр").
parent("Наталья", "Александр").
parent("Артем", "Мария").
parent("Наталья", "Мария").

is_man(Human) :- man(Human).
is_woman(Human) :- woman(Human).
are_married(Human1, Human2) :-
    married(Human1, Human2);
    married(Human2, Human1).
is_parent(Parent, Child) :- parent(Parent, Child).

% брат/сестра
are_siblings(Human1, Human2) :-
    is_parent(Parent, Human1),
    is_parent(Parent, Human2),
    Human1 \= Human2,
    is_woman(Parent).

% дедушка/бабушка
is_grandparent(Grandparent, Grandchild) :-
    is_parent(Grandparent, Parent),
    is_parent(Parent, Grandchild).

% внук/внучка
is_grandchild(Grandchild, Grandparent) :-
    is_grandparent(Grandparent, Grandchild).

% двоюродные брат/сестра
are_cousins(Human1, Human2) :-
    is_parent(Parent, Human1),
    are_siblings(Parent, ParentSibling),
    is_parent(ParentSibling, Human2).

% тетя/дядя
is_aunt_or_uncle(Aunt, Nephew) :-
    is_parent(Parent, Nephew),
    are_siblings(Parent, Aunt).

% свекровь/тесть
is_parent_in_law(ParentInLaw, ChildInLaw) :-
    are_married(ChildInLaw, Partner),
    is_parent(ParentInLaw, Partner).

% зять/невеста
is_child_in_law(ChildInLaw, ParentInLaw) :-
	is_parent_in_law(ParentInLaw, ChildInLaw).
