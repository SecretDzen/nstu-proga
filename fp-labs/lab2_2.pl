range_tail(0, 0, []).
range_tail(A, A, [A]).

range_tail(A, B, [A|T]) :-
    A < B,
    A1 is A + 1,
    range_tail(A1, B, T).

range([A, B], X) :-
    range_tail(A, B, X).

list_of_lists_range([], []).

list_of_lists_range(Inputs, Outputs) :-
    maplist(range, Inputs, Outputs).

maplist(_, [], []).
maplist(Pred, [H1|T1], [H2|T2]) :-
    call(Pred, H1, H2),
    maplist(Pred, T1, T2).
