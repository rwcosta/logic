existe(individuo).

donoDeSi(X) :- existe(X).

donoDoQueProduz(X) :- donoDeSi(X).

direitoLiberdadeExpressao(X) :- existe(X).

direitoBuscarFelicidade(X) :- existe(X).

naoOpcional(imposto).

ameacaDeViolencia(imposto).

coercao(X) :- naoOpcional(X), ameacaDeViolencia(X).

roubo(X, Y) :- donoDoQueProduz(Y), coercao(X).

