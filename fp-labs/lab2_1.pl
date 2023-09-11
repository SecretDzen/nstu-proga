pow_tail(_, 0, Acc, Acc).

pow_tail(X, N, Acc, Res) :-
    N > 0,
    N1 is N - 1,
    Acc1 is Acc * X,
    pow_tail(X, N1, Acc1, Res).

pow_tail(X, N, Res) :- pow_tail(X, N, 1, Res).

pow_non_tail(_, 0, 1).

pow_non_tail(X, N, Res) :-
    N1 is N - 1,
    pow_non_tail(X, N1, Res1),
    Res is Res1 * X.
