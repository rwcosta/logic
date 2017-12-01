homem(joao).
homem(pedro).
homem(carlos).

homem(flavio).

mulher(maria).
mulher(julia).
mulher(joyce).

mulher(marta).

pais(joao, pedro, maria).
pais(julia, pedro, maria).

pais(carlos, joao, marta).
pais(joyce, flavio, julia).

filho(X, Y) :- pais(X, Y, Mae); pais(X, Pai, Y).
irmao(X, Y) :- pais(X, Pai, Mae), pais(Y, Pai, Mae).
tio(X, Y)   :- (irmao(X, Pai), pais(Y, Pai, Cunhada)); (irmao(X, Mae), pais(Y, Cunhado, Mae)).
avo(X, Y)   :- (filho(Pai, X), pais(Y, Pai, Nora)); (filho(Mae, X), pais(Y, Genro, Mae)).
primo(X, Y) :- (tio(Pai, X), pais(Y, Pai, Tia)); (tio(Mae, X), pais(Y, Tio, Mae)).

