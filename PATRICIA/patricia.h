// MÁRCIO PAULINO, GUSTAVO SOUZA, MATHEUS GONÇALVES SANTOS , PEDRO MOURA SIMOES
#ifndef PATRICIA_H
#define PATRICIA_H
#include <stdlib.h>
#include <stdio.h>
#include "./lista/lista.h"

typedef struct{
    char chave[20];
 }TipoChave;

typedef enum {
  Interno, Externo
} TipoNo;

typedef struct TipoPatNo* TipoArvore; 

typedef struct TipoPatNo {
  TipoNo nt;
  union {             //o union é utilizado para separar o nó interno do nó externo , o interno é para as comparações e saber para qual lado vai , o externo é a palavra que vou guardar na patricia.
    struct {
      int posicao;    // aqui é a posicao que sera comparada da palavra para saber pra que lado vai.
      char caractere; // aqui é o caractere que sera comparado.
      TipoArvore Esq, Dir;
    } NInterno ;
    struct {
        TipoChave palavra;
        TipoListaOcorrencia ocorrencias;
    } NExterno;
  } NO;
} TipoPatNo;

//FUNÇÕES

void InicializaPatricia(TipoArvore *p);
short EExterno(TipoArvore p); // Funcao auxiliar para verificar se o nó é externo ou interno.
TipoArvore CriaNoInt(int i, char c, TipoArvore *Esq,  TipoArvore *Dir); // Funcao que cria um dos nos internos utilizados na comparação.
TipoArvore CriaNoExt(TipoChave palavra , int idDoc); // Funcao que cria um no externo que armazena uma palavra
void Pesquisa(TipoChave palavra, TipoArvore t, int *comp);
TipoArvore InsereEntrePatricia(TipoChave palavra, TipoArvore *t, int i, int idDoc, int *comp); // A insereEntre é utilizada depois que achou a posicao que difere as palavras
TipoArvore PegaPalavraQualquer(TipoArvore t);
void InserePatricia(TipoChave palavra, TipoArvore *t, int idDoc, int *comp); // A funcao que faz a inserção.
void ImprimePatricia(TipoArvore p);
TipoArvore BuscaNoPatricia(TipoChave palavra, TipoArvore t, int *comp);


#endif