homem(joao).
homem(pedro).
homem(carlos).
homem(carlosJr).

homem(flavio).
homem(cazuza).

mulher(maria).
mulher(julia).
mulher(joyce).
mulher(lisa).
mulher(graça).
mulher(paula).

mulher(marta).
mulher(luna).

pais(joao, pedro, maria).
pais(julia, pedro, maria).

pais(carlos, joao, marta).
pais(joyce, flavio, julia).

pais(carlosJr, carlos, luna).
pais(lisa, carlos, luna).
pais(graça, cazuza, joyce).
pais(paula, cazuza, joyce).

filho(X, Y) :- pais(X, Y, _); pais(X, _, Y).
irmao(X, Y) :- (X \== Y), pais(X, Pai, Mae), pais(Y, Pai, Mae).
tio(X, Y)   :- irmao(X, Z), (pais(Y, Z, _); pais(Y, _, Z)).
avo(X, Y)   :- filho(Z, X), (pais(Y, Z, _); pais(Y, _, Z)).
primo(X, Y) :- (X \== Y), (tio(Z, X), (pais(Y, Z, _); pais(Y, _, Z))).

