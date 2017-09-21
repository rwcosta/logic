// 
// Calcula a tabela-verdade para uma fórmula fixa
//

#include <stdio.h>

#define TRUE              1
#define FALSE             0

// macro para calcular o valor da implicacao
#define IMP(b1, b2)       (b1 && !b2 ? FALSE : TRUE)

// macro para calcular o valor da bi implicacao
#define BIMP(b1, b2)      (b1 == b2 ? TRUE : FALSE)

//
// A fórmula calculada pelo codigo eh' 
// (P -> Q) /\ (P -> R) <-> (Q -> R) \/ (Q -> P) 
//

// numero de variaveis proposicionais na formula
#define VARS              3

// constantes para os indices das tres variaveis
#define P                 0
#define Q                 1
#define R                 2

// representacao da formula
char nome[VARS];     // nome das variaveis
int I[VARS];         // interpretacao das variaveis

void inicializa_formula() 
{
  nome[P] = 'P';
  nome[Q] = 'Q';
  nome[R] = 'R';

  for (int c = 0; c < VARS; c++)
    I[c] = FALSE;
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

int valor_formula()
{
  return BIMP((IMP(I[P], I[Q]) && IMP(I[P], I[R])), (IMP(I[Q], I[R]) || IMP(I[Q], I[P])));
}

void mostra_tabela()
{
  int fim = FALSE,
      taut = TRUE, // Assume de inicio que a formula eh Tautologia
      satis = FALSE; // Assume de inicio que a formula nao eh Satisfatoria
  
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
    for (int c = 0; c < VARS; c++)
      if (I[c])
        printf(" T |");
      else
        printf(" F |");

    // calcula e imprime o valor da formula
    if (valor_formula()) {
      printf(" T\n");
      satis = TRUE; // Se um dos casos for T logo a formula eh Satisfatoria
    }
    else {
      printf(" F\n");
      taut = FALSE; // Se um dos casos for F logo a formula nao eh Tautologia
    }
    
    // verifica se acabou a tabela ou passa para
    // a proxima linha
    if (ultima_interpretacao())
      fim = TRUE;
    else
      proxima_interpretacao();
  }
  
  printf("\n");
  
  if(satis)
      printf("Fórmula é Satisfatória.\nFórmula não é Negação.\n");
  else
      printf("Fórmula não é Satisfatória.\nFórmula é Negação.\n");
  
  if(taut)
      printf("Fórmula é Tautologia.\n");
  else
      printf("Fórmula não é Tautologia.\n");
  
}

int main()
{
  printf("Calculo de tabela-verdade\n\n");

  mostra_tabela();

  return 0;
}
