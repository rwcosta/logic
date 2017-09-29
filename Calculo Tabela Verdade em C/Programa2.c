// Calculo de tabela verdade para formulas representadas
// com arvores sintaticas.

#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

// macro para calcular o valor da implicacao
#define IMPVAL(b1, b2)       (b1 && !b2 ? FALSE : TRUE)

// macro para calcular o valor de uma bi-implicacao
#define BIMPVAL(b1, b2)      (b1 == b2)

// tipo do no da arvore
typedef enum tagTipo {
  NEG, AND, OR, IMP, BIMP, P, Q, R
} Tipo;

// uma formula da logica
typedef struct tagForm
{
  Tipo tipo;
  struct tagForm *dir;
  struct tagForm *esq;
  int satis;
  int taut;
} Formula;

#define VARS   3
#define PIND   0
#define QIND   1
#define RIND   2

// representacao da formula
char nome[VARS];     // nome das variaveis
int I[VARS];         // interpretacao das variaveis

void inicializa_formula()
{
  nome[PIND] = 'P';
  nome[QIND] = 'Q';
  nome[RIND] = 'R';

  for (int c = 0; c < VARS; c++)
    I[c] = FALSE;
}

Formula* cria_formula(Tipo tipo, Formula *dir, Formula *esq)
{
  Formula *res = (Formula*) malloc(sizeof(Formula));

  if (res == NULL)
    return NULL;

  res->tipo = tipo;
  res->dir = dir;
  res->esq = esq;
  res->satis = FALSE; // Assume de inicio que a formula nao eh Satisfatoria
  res->taut = TRUE;   // Assume de inicio que a formula eh Tautologia

  return res;
}

Formula* neg(Formula *e)
{
  return cria_formula(NEG, e, NULL);
}

Formula* and(Formula *d, Formula *e)
{
  return cria_formula(AND, d, e);
}

Formula* or(Formula *d, Formula *e)
{
  return cria_formula(OR, d, e);
}

Formula* imp(Formula *d, Formula *e)
{
  return cria_formula(IMP, d, e);
}

Formula* bimp(Formula *d, Formula *e)
{
  return cria_formula(BIMP, d, e);
}

Formula* var_p()
{
  return cria_formula(P, NULL, NULL);
}

Formula* var_q()
{
  return cria_formula(Q, NULL, NULL);
}

Formula* var_r()
{
  return cria_formula(R, NULL, NULL);
}

// Libera o espaco de memoria ocupada por uma formula
void destroi_formula(Formula *f)
{
  if (f != NULL) {
    switch(f->tipo) {
    case AND:
    case OR:
    case IMP:
    case BIMP:
      destroi_formula(f->dir);
      destroi_formula(f->esq);
      break;

    case NEG:
      destroi_formula(f->dir);
      break;

    // outros casos sao de variaveis, que nao tem filhos
    }

    free(f);
  }
}

int indice_variavel(Tipo tipo)
{
  switch(tipo) {
  case P:
    return PIND;

  case Q:
    return QIND;

  case R:
    return RIND;

  default:   // demais tipos nao representam variaveis
    return -1;
  }
}

int valor_formula(Formula *f)
{
  switch(f->tipo) {
  case P:
  case Q:
  case R:
    return I[indice_variavel(f->tipo)];

  case NEG:
    return !valor_formula(f->dir);

  case AND:
    return valor_formula(f->dir) &&
           valor_formula(f->esq);

  case OR:
    return valor_formula(f->dir) ||
           valor_formula(f->esq);

  case IMP:
    return IMPVAL(valor_formula(f->dir),
                    valor_formula(f->esq));

  case BIMP:
    return BIMPVAL(valor_formula(f->dir),
                   valor_formula(f->esq));
  }
}

// retorna TRUE se a interpretacao atual eh a ultima na tabela-verdade
int ultima_interpretacao()
{
  int res = 1;

  for (int c = 0; c < VARS; c++) {
    res = res && I[c];
  }

  return res;
}

// altera a interpretacao atual no array I[] para a proxima na
// ordem da tabela-verdade
void proxima_interpretacao()
{
  int c = VARS - 1;

  while (c >= 0 && I[c] != 0) {
    I[c--] = 0;
  }

  if (c >= 0)
    I[c] = 1;
}

void mostra_tabela(Formula *f)
{
  int fim = FALSE;

  inicializa_formula();

  printf("Formula:\n");
  printf("H = (P -> Q) /\\ (P -> R) <-> (Q -> R) \\/ (Q -> P)\n\n");

  for (int c = 0; c < VARS; c++) {
    printf(" %c |", nome[c]);
  }
  printf(" H\n");

  for (int c = 0; c < 4 * VARS + 3; c++)
    printf("-");
  printf("\n");

  while (!fim) {
    // imprime valores atuais das variaveis
    for (int c = 0; c < VARS; c++) {
      if (I[c])
        printf(" T |");
      else
        printf(" F |");
    }

    // calcula e imprime o valor da formula
    if (valor_formula(f)) {
      printf(" T\n");
      f->satis = TRUE; // Se um dos casos for T logo a formula eh Satisfatoria
    }
    else {
      printf(" F\n");
      f->taut = FALSE; // Se um dos casos for F logo a formula nao eh Tautologia
    }

    // verifica se acabou a tabela ou passa para
    // a proxima linha
    if (ultima_interpretacao())
      fim = TRUE;
    else
      proxima_interpretacao();
  }
}

int main(int argc, char **argv)
{
  // (P -> Q) /\ (P -> R) <-> (Q -> R) \/ (Q -> P) 
  Formula *f = bimp(and(imp(var_p(), var_q()), imp(var_p(), var_r())), 
                    or(imp(var_q(), var_r()), imp(var_q(), var_p())));

  printf("Calculo de tabela-verdade\n\n");

  mostra_tabela(f);

  printf("\n");
  
  if(f->satis)
      printf("Fórmula é Satisfatória.\nFórmula não é Negação.\n");
  else
      printf("Fórmula não é Satisfatória.\nFórmula é Negação.\n");
  
  if(f->taut)
      printf("Fórmula é Tautologia.\n");
  else
      printf("Fórmula não é Tautologia.\n");
  
  destroi_formula(f);

  return 0;
}
