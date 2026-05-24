### Protokoll spko:

##### 5a)

von [Wikipedia](https://en.wikipedia.org/wiki/Logic_programming) inspirieren lassen:
```Prolog
fibonacci(0, 0).
fibonacci(1, 1).

fibonacci(N, Result) :-
    N > 1,
    N1 is N - 1,
    N2 is N - 2,
    fibonacci(N1, F1),
    fibonacci(N2, F2),
    Result is F1 + F2.
```

```Prolog
fak(0,1).
fak(N,Result) :-
    N > 0,
    N1 is N - 1,
    fak(N1,F1),
    Result is N * F1.
```

oder mit Endrekursion:
```Prolog
fak(N, Result) :-
    fak_acc(N, 1, Result).

fak_acc(0, Acc, Acc).

fak_acc(N, Acc, Result) :-
    N > 0,
    NewAcc is Acc * N,
    N1 is N - 1,
    fak_acc(N1, NewAcc, Result).
```
fak(3,R) R=6


##### Was berechnen folgende Anfragen? 
?– append(X, Y, [1,2,3,4]).
?- append(X, [1,2,3,4], Y).
Basisfall append([],L,L)
X=[], Y=L=[1,2,3,4,4]

##### 5b)
Der sum funktor ist fast identisch mit dem vorgegebenen listlen funktor.
Ohne Accumulator:
```Prolog
sum([],0).
sum([F|L],Result) :-
    sum(L,N1),
    Result is N1+F.
```
Mit Accumulator:
```Prolog
sum(L,R) :- sumacc(L,0,R).
sumacc([],A,A).

sumacc([F|L],A,R) :-
    A1 is A+F,
    sumacc(L,A1,R).
```
?- sum([1,2,3],R)
R=6


##### 5c)

>Expert systems were already outliers in much of the business world, requiring new skills that many IT departments did not have and were not eager to develop.
>-[wikipedia](https://en.wikipedia.org/wiki/Expert_system).

Das Zug-Verbindungs Programm verwendet 2 Rekursions Funktionen. ich habe mir überlegt ob ich die append Funktion aus den Folien verwende, dann wären es 3 rekursive Funktionen gewesen. Es hat jedoch leider nicht funktioniert, da "append(R,zug(S1,Z3,S2,Z4),R)" ein Vergleich ist der immer fehlschlägt.

```Prolog
verbindung(S1,AZ,S2,[zug(S1,Z1,S2,Z2)]) :-
    zug(S1,Z1,S2,Z2),
    AZ =< Z1,!.

verbindung(S1, AZ, S2, R) :-
    zug(S1,Z1,Zstadt,Z2),
    AZ =< Z1,
    R = [zug(S1,Z1,Zstadt,Z2)|Rest],
    umsteigen(Zstadt,Z2,S2,Rest).

umsteigen(S1,Z1,S2,[zug(S1,Z3,S2,Z4)]) :-
    zug(S1,Z3,S2,Z4),
    Z1 < Z3,!.
    
umsteigen(S1,Z1,S2,[zug(S1,Z3,Zstadt,Z4)|Rest]) :-
    zug(S1,Z3,Zstadt,Z4),
    Z1 < Z3,
    umsteigen(Zstadt,Z4,S2,Rest).
```

verbindungs prädikat muss nicht rekursiv sein, da es nur dazu dient eine Direkt-Verbindung abzufangen und umsteigen aufzurufen. Diese Alternative wäre auch möglich gewesen:

```Prolog
verbindung(S1, AZ, S2, R) :-
    zug(S1, Z1, Zstadt, Z2),
    AZ =< Z1,
    (   Zstadt = S2, R = [zug(S1, Z1, S2, Z2)],!
    ;   R = [zug(S1, Z1, Zstadt, Z2) | Rest],
        umsteigen(Zstadt, Z2, S2, Rest)
    ).
```

Umsteigen() nimmt immer die letzte Zwischenstation und versucht zum Ziel zufahren, falls es nicht geht, zur ersten Station die nach der letzten Zugfahrt erreichbar ist. Dies wird solange wiederholt bis das Ziel erreichbar ist. Die Laufzeit ist im schlimmsten Fall exponentiell.
